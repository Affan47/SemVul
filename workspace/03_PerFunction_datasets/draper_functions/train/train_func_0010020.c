vim_fnamencmp(x, y, len)
    char_u	*x, *y;
    size_t	len;
{
#ifdef BACKSLASH_IN_FILENAME
    char_u	*px = x;
    char_u	*py = y;
    int		cx = NUL;
    int		cy = NUL;

    while (len > 0)
    {
	cx = PTR2CHAR(px);
	cy = PTR2CHAR(py);
	if (cx == NUL || cy == NUL
	    || ((p_fic ? MB_TOLOWER(cx) != MB_TOLOWER(cy) : cx != cy)
		&& !(cx == '/' && cy == '\\')
		&& !(cx == '\\' && cy == '/')))
	    break;
	len -= MB_PTR2LEN(px);
	px += MB_PTR2LEN(px);
	py += MB_PTR2LEN(py);
    }
    if (len == 0)
	return 0;
    return (cx - cy);
#else
    if (p_fic)
	return MB_STRNICMP(x, y, len);
    return STRNCMP(x, y, len);
#endif
}
