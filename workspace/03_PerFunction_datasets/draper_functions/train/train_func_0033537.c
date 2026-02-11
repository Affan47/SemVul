getargopt(eap)
    exarg_T	*eap;
{
    char_u	*arg = eap->arg + 2;
    int		*pp = NULL;
#ifdef FEAT_MBYTE
    int		bad_char_idx;
    char_u	*p;
#endif


    if (STRNCMP(arg, "bin", 3) == 0 || STRNCMP(arg, "nobin", 5) == 0)
    {
	if (*arg == 'n')
	{
	    arg += 2;
	    eap->force_bin = FORCE_NOBIN;
	}
	else
	    eap->force_bin = FORCE_BIN;
	if (!checkforcmd(&arg, "binary", 3))
	    return FAIL;
	eap->arg = skipwhite(arg);
	return OK;
    }


    if (STRNCMP(arg, "edit", 4) == 0)
    {
	eap->read_edit = TRUE;
	eap->arg = skipwhite(arg + 4);
	return OK;
    }

    if (STRNCMP(arg, "ff", 2) == 0)
    {
	arg += 2;
	pp = &eap->force_ff;
    }
    else if (STRNCMP(arg, "fileformat", 10) == 0)
    {
	arg += 10;
	pp = &eap->force_ff;
    }
#ifdef FEAT_MBYTE
    else if (STRNCMP(arg, "enc", 3) == 0)
    {
	if (STRNCMP(arg, "encoding", 8) == 0)
	    arg += 8;
	else
	    arg += 3;
	pp = &eap->force_enc;
    }
    else if (STRNCMP(arg, "bad", 3) == 0)
    {
	arg += 3;
	pp = &bad_char_idx;
    }
#endif

    if (pp == NULL || *arg != '=')
	return FAIL;

    ++arg;
    *pp = (int)(arg - eap->cmd);
    arg = skip_cmd_arg(arg, FALSE);
    eap->arg = skipwhite(arg);
    *arg = NUL;

#ifdef FEAT_MBYTE
    if (pp == &eap->force_ff)
    {
#endif
	if (check_ff_value(eap->cmd + eap->force_ff) == FAIL)
	    return FAIL;
#ifdef FEAT_MBYTE
    }
    else if (pp == &eap->force_enc)
    {

	for (p = eap->cmd + eap->force_enc; *p != NUL; ++p)
	    *p = TOLOWER_ASC(*p);
    }
    else
    {


	p = eap->cmd + bad_char_idx;
	if (STRICMP(p, "keep") == 0)
	    eap->bad_char = BAD_KEEP;
	else if (STRICMP(p, "drop") == 0)
	    eap->bad_char = BAD_DROP;
	else if (MB_BYTE2LEN(*p) == 1 && p[1] == NUL)
	    eap->bad_char = *p;
	else
	    return FAIL;
    }
#endif

    return OK;
}
