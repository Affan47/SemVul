ex_global(eap)
    exarg_T	*eap;
{
    linenr_T	lnum;
    int		ndone = 0;
    int		type;
    char_u	*cmd;

    char_u	delim;
    char_u	*pat;
    regmmatch_T	regmatch;
    int		match;
    int		which_pat;

    if (global_busy)
    {
	EMSG(_("E147: Cannot do :global recursive"));
	return;
    }

    if (eap->forceit)
	type = 'v';
    else
	type = *eap->cmd;
    cmd = eap->arg;
    which_pat = RE_LAST;
    sub_nsubs = 0;
    sub_nlines = 0;


    if (*cmd == '\\')
    {
	++cmd;
	if (vim_strchr((char_u *)"/?&", *cmd) == NULL)
	{
	    EMSG(_(e_backslash));
	    return;
	}
	if (*cmd == '&')
	    which_pat = RE_SUBST;
	else
	    which_pat = RE_SEARCH;
	++cmd;
	pat = (char_u *)"";
    }
    else if (*cmd == NUL)
    {
	EMSG(_("E148: Regular expression missing from global"));
	return;
    }
    else
    {
	delim = *cmd;
	if (delim)
	    ++cmd;
	pat = cmd;
	cmd = skip_regexp(cmd, delim, p_magic, &eap->arg);
	if (cmd[0] == delim)
	    *cmd++ = NUL;
    }

#ifdef FEAT_FKMAP
    if (p_altkeymap && curwin->w_p_rl)
	lrFswap(pat,0);
#endif

    if (search_regcomp(pat, RE_BOTH, which_pat, SEARCH_HIS, &regmatch) == FAIL)
    {
	EMSG(_(e_invcmd));
	return;
    }


    for (lnum = eap->line1; lnum <= eap->line2 && !got_int; ++lnum)
    {

	match = vim_regexec_multi(&regmatch, curwin, curbuf, lnum,
							    (colnr_T)0, NULL);
	if ((type == 'g' && match) || (type == 'v' && !match))
	{
	    ml_setmarked(lnum);
	    ndone++;
	}
	line_breakcheck();
    }


    if (got_int)
	MSG(_(e_interr));
    else if (ndone == 0)
    {
	if (type == 'v')
	    smsg((char_u *)_("Pattern found in every line: %s"), pat);
	else
	    smsg((char_u *)_(e_patnotf2), pat);
    }
    else
	global_exe(cmd);

    ml_clearmarked();
    vim_free(regmatch.regprog);
}
