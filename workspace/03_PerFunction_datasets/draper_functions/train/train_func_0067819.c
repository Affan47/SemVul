insstr(s)
	register char_u  *s;
{
	register char_u		*old, *new;
	register int		newlen = STRLEN(s);
	int					oldlen;
	colnr_t				col = curwin->w_cursor.col;
	linenr_t			lnum = curwin->w_cursor.lnum;

	old = ml_get(lnum);
	oldlen = STRLEN(old);
	new = alloc((unsigned)(oldlen + newlen + 1));
	if (new == NULL)
		return;
	memmove((char *)new, (char *)old, (size_t)col);
	memmove((char *)new + col, (char *)s, (size_t)newlen);
	memmove((char *)new + col + newlen, (char *)old + col, (size_t)(oldlen - col + 1));
	ml_replace(lnum, new, FALSE);
	curwin->w_cursor.col += newlen;
	CHANGED;
}
