m_fword(m, cnt, cmd)
	MARK	m;
	long	cnt;
	int	cmd;
{
	REG long	l;
	REG char	*text;
	REG int		i;

	DEFAULT(1);

	l = markline(m);
	pfetch(l);
	text = ptext + markidx(m);
	while (cnt-- > 0)
	{
		i = *text++;

		if (cmd == 'W')
		{

			while (i && (!isascii(i) || !isspace(i)))
			{
				i = *text++;
			}
		}
		else if (!isascii(i) || isalnum(i) || i == '_')
		{

			while (i && (!isascii(i) || isalnum(i) || i == '_'))
			{
				i = *text++;
			}
		}
		else
		{

			while (i && isascii(i) && !isalnum(i) && !isspace(i))
			{
				i = *text++;
			}
		}


		while (!i || isascii(i) && isspace(i))
		{

			if (!i)
			{

				l++;
				if (l > nlines)
				{
					return MARK_UNSET;
				}
				pfetch(l);
				text = ptext;
			}

			i = *text++;
		}
		text--;
	}


	m = buildmark(text);
	return m;
}
