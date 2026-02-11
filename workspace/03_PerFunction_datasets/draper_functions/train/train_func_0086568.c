addSuppression(const std::string &errorId, const std::string &file, unsigned int line)
{

    if (errorId.empty()) {
        return "Failed to add suppression. No id.";
    }
    if (errorId != "*") {
        for (std::string::size_type pos = 0; pos < errorId.length(); ++pos) {
            if (errorId[pos] < 0 || (!std::isalnum(errorId[pos]) &&  errorId[pos] != '_')) {
                return "Failed to add suppression. Invalid id \"" + errorId + "\"";
            }
            if (pos == 0 && std::isdigit(errorId[pos])) {
                return "Failed to add suppression. Invalid id \"" + errorId + "\"";
            }
        }
    }

    return _suppressions[errorId].addFile(file, line);
}
