AbbrevExpand()
{
	char	wordbuf[100];
	register char
		*wp = wordbuf,
		*cp;
	int	col;
	register char	c;
	int	UC_count = 0;
	struct abbrev	*ap;

	col = curchar;
	while (col != 0 && jisident(linebuf[col - 1]))
		col -= 1;
	if (curchar-col >= (int)sizeof(wordbuf))
		return;

	while (col < curchar) {
		c = linebuf[col];
		if (AutoCaseAbbrev && jisupper(c)) {
			UC_count += 1;
			c = CharDowncase(c);
		}
		*wp++ = c;
		col += 1;
	}
	*wp = '\0';

	if ((ap = lookup_abbrev(A_tables[curbuf->b_major], wordbuf)) != NULL
	|| (ap = lookup_abbrev(A_tables[GLOBAL], wordbuf)) != NULL)
	{
		del_char(BACKWARD, (wp - wordbuf), NO);

		for (cp = ap->a_phrase; (c = *cp) != '\0'; ) {
			if (UC_count > 0 && jislower(c)
			&& (cp == ap->a_phrase
			   || (UC_count > 1 && (jiswhite(cp[-1]) || cp[-1] == '-'))))
				c = CharUpcase(c);
			insert_c(c, 1);
			cp += 1;
		}
		if (ap->a_cmdhook != NULL)
			ExecCmd(ap->a_cmdhook);
	}
}
