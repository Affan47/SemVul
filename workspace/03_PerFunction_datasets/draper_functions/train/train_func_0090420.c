isKeyword(const char *current, const char *keyword) {
    int pos = 0;
    for (; keyword[pos]; ++pos) {
        if (!current[pos] || std::tolower(current[pos]) != std::tolower(keyword[pos])) {
            return 0;
        }
    }
    return pos;
}
