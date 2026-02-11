getChar (void)
{
	int c;

	if (Ungetc != '\0')
	{
		c = Ungetc;
		Ungetc = '\0';
	}
	else if (FreeSourceForm)
		c = getFreeFormChar ();
	else
		c = getFixedFormChar ();
	return c;
}
