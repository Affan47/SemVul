f_byteidx(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
#ifdef FEAT_MBYTE
    char_u	*t;
#endif
    char_u	*str;
    long	idx;

    str = get_tv_string_chk(&argvars[0]);
    idx = get_tv_number_chk(&argvars[1], NULL);
    rettv->vval.v_number = -1;
    if (str == NULL || idx < 0)
	return;

#ifdef FEAT_MBYTE
    t = str;
    for ( ; idx > 0; idx--)
    {
	if (*t == NUL)
	    return;
	t += (*mb_ptr2len)(t);
    }
    rettv->vval.v_number = (varnumber_T)(t - str);
#else
    if ((size_t)idx <= STRLEN(str))
	rettv->vval.v_number = idx;
#endif
}
