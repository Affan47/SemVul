parseIdentifier (
		const unsigned char *cp, vString *const identifier)
{
	vStringClear (identifier);
	while (isIdentifierCharacter ((int) *cp))
	{
		vStringPut (identifier, (int) *cp);
		++cp;
	}
	vStringTerminate (identifier);
	return cp;
}
