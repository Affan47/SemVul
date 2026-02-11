skipToEndOfString (boolean ignoreBackslash)
{
	int c;

	while ((c = fileGetc ()) != EOF)
	{
		if (c == BACKSLASH && ! ignoreBackslash)
			fileGetc ();
		else if (c == DOUBLE_QUOTE)
			break;
	}
	return STRING_SYMBOL;
}
