eatComment (lexingState * st)
{
	boolean unfinished = TRUE;
	boolean lastIsStar = FALSE;
	const unsigned char *c = st->cp + 2;

	while (unfinished)
	{


		if (c == NULL || *c == '\0')
		{
			st->cp = fileReadLine ();


			if (st->cp == NULL)
				return;
			c = st->cp;
			continue;
		}

		else if (*c == ')' && lastIsStar)
			unfinished = FALSE;


		else if (c[0] == '(' && c[1] == '*')
		{
			st->cp = c;
			eatComment (st);
			c = st->cp;
			lastIsStar = FALSE;
		}
		else
			lastIsStar = '*' == *c;

		c++;
	}

	st->cp = c;
}
