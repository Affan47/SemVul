ex_wincmd(eap)
    exarg_T	*eap;
{
    int		xchar = NUL;
    char_u	*p;

    if (*eap->arg == 'g' || *eap->arg == Ctrl_G)
    {

	if (eap->arg[1] == NUL)
	{
	    EMSG(_(e_invarg));
	    return;
	}
	xchar = eap->arg[1];
	p = eap->arg + 2;
    }
    else
	p = eap->arg + 1;

    eap->nextcmd = check_nextcmd(p);
    p = skipwhite(p);
    if (*p != NUL && *p != '"' && eap->nextcmd == NULL)
	EMSG(_(e_invarg));
    else if (!eap->skip)
    {

	postponed_split_flags = cmdmod.split;
	postponed_split_tab = cmdmod.tab;
	do_window(*eap->arg, eap->addr_count > 0 ? eap->line2 : 0L, xchar);
	postponed_split_flags = 0;
	postponed_split_tab = 0;
    }
}
