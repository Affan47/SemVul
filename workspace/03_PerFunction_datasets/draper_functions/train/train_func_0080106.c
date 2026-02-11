f_tolower(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    char_u	*p;

    p = vim_strsave(get_tv_string(&argvars[0]));
    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = p;

    if (p != NULL)
	while (*p != NUL)
	{
#ifdef FEAT_MBYTE
	    int		l;

	    if (enc_utf8)
	    {
		int c, lc;

		c = utf_ptr2char(p);
		lc = utf_tolower(c);
		l = utf_ptr2len(p);

		if (utf_char2len(lc) == l)
		    utf_char2bytes(lc, p);
		p += l;
	    }
	    else if (has_mbyte && (l = (*mb_ptr2len)(p)) > 1)
		p += l;
	    else
#endif
	    {
		*p = TOLOWER_LOC(*p);
		++p;
	    }
	}
}
