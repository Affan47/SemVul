syn_cmd_case(eap, syncing)
    exarg_T	*eap;
    int		syncing;
{
    char_u	*arg = eap->arg;
    char_u	*next;

    eap->nextcmd = find_nextcmd(arg);
    if (eap->skip)
	return;

    next = skiptowhite(arg);
    if (STRNICMP(arg, "match", 5) == 0 && next - arg == 5)
	curbuf->b_syn_ic = FALSE;
    else if (STRNICMP(arg, "ignore", 6) == 0 && next - arg == 6)
	curbuf->b_syn_ic = TRUE;
    else
	EMSG2(_("E390: Illegal argument: %s"), arg);
}
