f_feedkeys(argvars, rettv)
    typval_T    *argvars;
    typval_T    *rettv UNUSED;
{
    int		remap = TRUE;
    char_u	*keys, *flags;
    char_u	nbuf[NUMBUFLEN];
    int		typed = FALSE;
    char_u	*keys_esc;


    if (check_secure())
	return;

    keys = get_tv_string(&argvars[0]);
    if (*keys != NUL)
    {
	if (argvars[1].v_type != VAR_UNKNOWN)
	{
	    flags = get_tv_string_buf(&argvars[1], nbuf);
	    for ( ; *flags != NUL; ++flags)
	    {
		switch (*flags)
		{
		    case 'n': remap = FALSE; break;
		    case 'm': remap = TRUE; break;
		    case 't': typed = TRUE; break;
		}
	    }
	}


	keys_esc = vim_strsave_escape_csi(keys);
	if (keys_esc != NULL)
	{
	    ins_typebuf(keys_esc, (remap ? REMAP_YES : REMAP_NONE),
					       typebuf.tb_len, !typed, FALSE);
	    vim_free(keys_esc);
	    if (vgetc_busy)
		typebuf_was_filled = TRUE;
	}
    }
}
