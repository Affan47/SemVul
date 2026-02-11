typesMatch(const std::string& iToTest, const std::string& iTypename, const std::string& iOptionalPrefix = "std::")
{
    return (iToTest == iTypename) || (iToTest == iOptionalPrefix + iTypename);
}
