m_fparagraph(m, cnt)
	MARK	m;
	long	cnt;
{
	char	*text;
	char	*pscn;
	long	l;

	DEFAULT(1);

	for (l = markline(m); cnt > 0 && l++ < nlines; )
	{
		text = fetchline(l);
		if (!*text)
		{
			cnt--;
		}
#ifndef NO_SENTENCE
		else if (*text == '.')
		{
			for (pscn = o_paragraphs; pscn[0] && pscn[1]; pscn += 2)
			{
				if (pscn[0] == text[1] && pscn[1] == text[2])
				{
					cnt--;
					break;
				}
			}
		}
#endif
	}
	if (l <= nlines)
	{
		m = MARK_AT_LINE(l);
	}
	else
	{
		m = MARK_LAST;
	}
	return m;
}
