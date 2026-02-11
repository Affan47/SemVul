ContainsNonprintableExceptSpaces(void) const
{
	size_t strLen = strlen(sharedString->c_str);
	unsigned i;
	for (i=0; i < strLen; i++)
	{
		if (sharedString->c_str[i] < ' ' || sharedString->c_str[i] >126)
			return true;
	}
	return false;
}
