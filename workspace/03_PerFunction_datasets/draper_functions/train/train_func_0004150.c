IoLexer_currentLineNumberOld(IoLexer *self)
{
	size_t lineNumber = 1;
	char *s = self->s;

	while (s < self->current)
	{
		if (*s == '\n')
		{
			lineNumber ++;
		}

		s ++;
	}

	return lineNumber;
}
