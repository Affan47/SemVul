strip_c(from, to)
char	*from,
	*to;
{
	register char
		*fr_p = from,
		*to_p = to,
		c;

	while ((c = *fr_p) == '\n' || jiswhite(c))
		fr_p += 1;
	while ((c = *fr_p) != '\0') {
		if (c != '\n')
			*to_p++ = c;
		fr_p += 1;
	}
	while (to_p > to && jiswhite(to_p[-1]))
		to_p -= 1;
	*to_p = '\0';
}
