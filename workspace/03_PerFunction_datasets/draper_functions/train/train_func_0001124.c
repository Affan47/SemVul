searchc(c, k, dir, type, count)
	int				k;
#endif
	int 			c;
	register int	dir;
	int 			type;
	long			count;
{
	static int	 	lastc = NUL;
#ifdef KANJI
	static int		lastk = NUL;
#endif
	static int		lastcdir;
	static int		lastctype;
	register int	col;
	char_u			*p;
	int 			len;

	if (c != NUL)
	{
		lastc = c;
#ifdef KANJI
		lastk = k;
#endif
		lastcdir = dir;
		lastctype = type;
	}
	else
	{
		if (lastc == NUL)
			return FALSE;
		if (dir)
			dir = -lastcdir;
		else
			dir = lastcdir;
	}

	p = ml_get(curwin->w_cursor.lnum);
	col = curwin->w_cursor.col;
	len = STRLEN(p);


	while (count--)
	{
			for (;;)
			{
#ifdef KANJI
				if (dir > 0 && ISkanji(p[col])) col ++;
				col += dir;
				if (dir < 0 && ISkanjiPosition(p, col + 1) == 2) col --;

				if (col < 0 || col >= len)
					return FALSE;

				if (ISkanji(p[col]))
				{
					if (p[col] == lastc && p[col + 1] == lastk)
						break;
				}
				else if (p[col] == lastc)
					break;
#else
				if ((col += dir) < 0 || col >= len)
					return FALSE;
				if (p[col] == lastc)
						break;
#endif
			}
	}
	if (lastctype)
#ifdef KANJI
	{
		if (dir < 0 && ISkanji(p[col]))
			col ++;
		col -= dir;
		if (dir > 0 && ISkanjiPosition(p, col + 1) == 2)
			col --;
    }
#else
		col -= dir;
#endif
	curwin->w_cursor.col = col;
	return TRUE;
}
