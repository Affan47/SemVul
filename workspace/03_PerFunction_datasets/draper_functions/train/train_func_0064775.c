parseCharacter (void)
{
	int c = fileGetc ();
	int result = c;

	if (c == '%')
		result = parseEscapedCharacter ();

	c = fileGetc ();
	if (c != '\'')
		skipToCharacter ('\n');

	return result;
}
