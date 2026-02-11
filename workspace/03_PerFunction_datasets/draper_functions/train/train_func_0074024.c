startsWithLower(const String& s)
{
	for (unsigned int i = 0; i < s.length(); i++) {
		if (tolower((*this)[i]) != s[i])
			return false;
	}
	return true;
}
