isSuppressedLocal(const std::string &errorId, const std::string &file, unsigned int line)
{
    if (errorId != "unmatchedSuppression" && _suppressions.find("*") != _suppressions.end())
        if (_suppressions["*"].isSuppressedLocal(file, line))
            return true;

    if (_suppressions.find(errorId) == _suppressions.end())
        return false;

    return _suppressions[errorId].isSuppressedLocal(file, line);
}
