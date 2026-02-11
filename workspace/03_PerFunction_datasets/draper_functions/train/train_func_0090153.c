isSeparator(const int character) const
{
    std::string::size_type ret = separators.find(character);
    if (ret == std::string::npos) {
	return false;
    } else {
	return true;
    }
}
