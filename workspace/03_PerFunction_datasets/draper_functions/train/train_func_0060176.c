cin_ispreproc(s)
    char_u *s;
{
    s = skipwhite(s);
    if (*s == '#')
	return TRUE;
    return FALSE;
}
