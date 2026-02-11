ex_breakadd(eap)
    exarg_T	*eap;
{
    struct debuggy *bp;
    char_u	*pat;
    garray_T	*gap;

    gap = &dbg_breakp;
#ifdef FEAT_PROFILE
    if (eap->cmdidx == CMD_profile)
	gap = &prof_ga;
#endif

    if (dbg_parsearg(eap->arg, gap) == OK)
    {
	bp = &DEBUGGY(gap, gap->ga_len);
	bp->dbg_forceit = eap->forceit;

	pat = file_pat_to_reg_pat(bp->dbg_name, NULL, NULL, FALSE);
	if (pat != NULL)
	{
	    bp->dbg_prog = vim_regcomp(pat, RE_MAGIC + RE_STRING);
	    vim_free(pat);
	}
	if (pat == NULL || bp->dbg_prog == NULL)
	    vim_free(bp->dbg_name);
	else
	{
	    if (bp->dbg_lnum == 0)
		bp->dbg_lnum = 1;
#ifdef FEAT_PROFILE
	    if (eap->cmdidx != CMD_profile)
#endif
	    {
		DEBUGGY(gap, gap->ga_len).dbg_nr = ++last_breakp;
		++debug_tick;
	    }
	    ++gap->ga_len;
	}
    }
}
