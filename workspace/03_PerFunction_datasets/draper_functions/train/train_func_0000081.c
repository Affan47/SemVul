FindMatch(dir)
int	dir;
{
	register Bufpos	*bp;
	register char	c = linebuf[curchar];

	if (strchr(p_types, c) == NULL || backslashed(linebuf, curchar))
		complain((char *)NULL);
	if (dir == FORWARD)
		f_char(1);
	bp = m_paren(c, dir, YES, NO);
	if (dir == FORWARD)
		b_char(1);
	if (bp != NULL)
		SetDot(bp);
	mp_error();

}
