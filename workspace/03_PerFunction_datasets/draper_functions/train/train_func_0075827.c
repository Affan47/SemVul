f_nr2char(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    char_u	buf[NUMBUFLEN];

#ifdef FEAT_MBYTE
    if (has_mbyte)
	buf[(*mb_char2bytes)((int)get_tv_number(&argvars[0]), buf)] = NUL;
    else
#endif
    {
	buf[0] = (char_u)get_tv_number(&argvars[0]);
	buf[1] = NUL;
    }
    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = vim_strsave(buf);
}
