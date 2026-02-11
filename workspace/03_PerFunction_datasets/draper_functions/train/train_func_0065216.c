fnamecmp_ino(fname_c, fname_s, ino_block0)
    char_u	*fname_c;
    char_u	*fname_s;
    long	ino_block0;
{
    struct stat	st;
    ino_t	ino_c = 0;
    ino_t	ino_s;
    char_u	buf_c[MAXPATHL];
    char_u	buf_s[MAXPATHL];
    int		retval_c;
    int		retval_s;

    if (mch_stat((char *)fname_c, &st) == 0)
	ino_c = (ino_t)st.st_ino;


    if (mch_stat((char *)fname_s, &st) == 0)
	ino_s = (ino_t)st.st_ino;
    else
	ino_s = (ino_t)ino_block0;

    if (ino_c && ino_s)
	return (ino_c != ino_s);


    retval_c = vim_FullName(fname_c, buf_c, MAXPATHL, TRUE);
    retval_s = vim_FullName(fname_s, buf_s, MAXPATHL, TRUE);
    if (retval_c == OK && retval_s == OK)
	return (STRCMP(buf_c, buf_s) != 0);


    if (ino_s == 0 && ino_c == 0 && retval_c == FAIL && retval_s == FAIL)
	return FALSE;
    return TRUE;
}
