#include "StringUtils.h"

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    if (start < 0) {
        start += str.size();
    }
    if (end <= 0) {
        end += str.size();
    }
    return str.substr(start, end - start);
}

std::string Capitalize(const std::string &str) noexcept{
    if (str.empty()) {
        return str;
    }
    std::string result = str;
    result[0] = std::toupper(result[0]);
    return result;
}

std::string Upper(const std::string &str) noexcept{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string Lower(const std::string &str) noexcept{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string LStrip(const std::string &str) noexcept{
    auto it = std::find_if_not(str.begin(), str.end(), ::isspace);
    return std::string(it, str.end());
}

std::string RStrip(const std::string &str) noexcept{
    auto it = std::find_if_not(str.rbegin(), str.rend(), ::isspace);
    return std::string(str.begin(), it.base());
}

std::string Strip(const std::string &str) noexcept{
    return LStrip(RStrip(str));
}

std::string Center(const std::string &str, int width, char fill) noexcept{
    int pad = width - str.size();
    if (pad <= 0) {
        return str;
    }
    int leftPad = pad / 2;
    int rightPad = pad - leftPad;
    return std::string(leftPad, fill) + str + std::string(rightPad, fill);
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    int pad = width - str.size();
    if (pad <= 0) {
        return str;
    }
    return str + std::string(pad, fill);
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    int pad = width - str.size();
    if (pad <= 0) {
        return str;
    }
    return std::string(pad, fill) + str;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(old, pos)) != std::string::npos) {
        result.replace(pos, old.size(), rep);
        pos += rep.size();
    }
    return result;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> result;
    std::string delimiter = splt.empty() ? " " : splt;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start));
    return result;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    std::ostringstream oss;
    std::copy(vect.begin(), vect.end(), std::ostream_iterator<std::string>(oss, delimiter.c_str()));
    std::string result = oss.str();
    if (!delimiter.empty() && result.size() >= delimiter.size()) {
        result.erase(result.size() - delimiter.size());
    }
    return result;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    std::string result;
    for (char ch : str) {
        if (ch == '\t') {
            result += std::string(tabsize - result.size() % tabsize, ' ');
        } else {
            result.push_back(ch);
        }
    }
    return result;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    // Convert strings to lowercase if ignorecase is true
    std::string str1 = (ignorecase) ? StringUtils::Lower(left) : left;
    std::string str2 = (ignorecase) ? StringUtils::Lower(right) : right;

    // Initialize a matrix to store distances
    std::vector<std::vector<int>> distanceMatrix(str1.length() + 1, std::vector<int>(str2.length() + 1, 0));

    // Initialize the matrix with the distances from each prefix to an empty string
    for (int i = 0; i <= static_cast<int>(str1.length()); ++i) {
        distanceMatrix[i][0] = i;
    }

    for (int j = 0; j <= static_cast<int>(str2.length()); ++j) {
        distanceMatrix[0][j] = j;
    }

    // Fill in the matrix
    for (int i = 1; i <= static_cast<int>(str1.length()); ++i) {
        for (int j = 1; j <= static_cast<int>(str2.length()); ++j) {
            int substitutionCost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            distanceMatrix[i][j] = std::min({
                distanceMatrix[i - 1][j] + 1,          // Deletion
                distanceMatrix[i][j - 1] + 1,          // Insertion
                distanceMatrix[i - 1][j - 1] + substitutionCost  // Substitution
            });
        }
    }

    // The bottom-right cell contains the Levenshtein distance
    return distanceMatrix[str1.length()][str2.length()];
    return 0;
}

};