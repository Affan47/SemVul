cin_isinit(void)
{
    char_u	*s;

    s = cin_skipcomment(ml_get_curline());

    if (STRNCMP(s, "typedef", 7) == 0 && !vim_isIDc(s[7]))
	s = cin_skipcomment(s + 7);

    if (STRNCMP(s, "static", 6) == 0 && !vim_isIDc(s[6]))
	s = cin_skipcomment(s + 6);

    if (STRNCMP(s, "enum", 4) == 0 && !vim_isIDc(s[4]))
	return TRUE;

    if (cin_ends_in(s, (char_u *)"=", (char_u *)"{"))
	return TRUE;

    return FALSE;
}
