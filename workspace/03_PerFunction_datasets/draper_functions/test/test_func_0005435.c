read_viminfo_search_pattern(virp, force)
    vir_T	*virp;
    int		force;
{
    char_u	*lp;
    int		idx = -1;
    int		magic = FALSE;
    int		no_scs = FALSE;
    int		off_line = FALSE;
    int		off_end = 0;
    long	off = 0;
    int		setlast = FALSE;
#ifdef FEAT_SEARCH_EXTRA
    static int	hlsearch_on = FALSE;
#endif
    char_u	*val;


    lp = virp->vir_line;
    if (lp[0] == '~' && (lp[1] == 'm' || lp[1] == 'M'))
    {
	if (lp[1] == 'M')
	    magic = TRUE;
	if (lp[2] == 's')
	    no_scs = TRUE;
	if (lp[3] == 'L')
	    off_line = TRUE;
	if (lp[4] == 'E')
	    off_end = SEARCH_END;
	lp += 5;
	off = getdigits(&lp);
    }
    if (lp[0] == '~')
    {
	setlast = TRUE;
	lp++;
    }
    if (lp[0] == '/')
	idx = RE_SEARCH;
    else if (lp[0] == '&')
	idx = RE_SUBST;
#ifdef FEAT_SEARCH_EXTRA
    else if (lp[0] == 'h')
	hlsearch_on = FALSE;
    else if (lp[0] == 'H')
	hlsearch_on = TRUE;
#endif
    if (idx >= 0)
    {
	if (force || spats[idx].pat == NULL)
	{
	    val = viminfo_readstring(virp, (int)(lp - virp->vir_line + 1),
									TRUE);
	    if (val != NULL)
	    {
		set_last_search_pat(val, idx, magic, setlast);
		vim_free(val);
		spats[idx].no_scs = no_scs;
		spats[idx].off.line = off_line;
		spats[idx].off.end = off_end;
		spats[idx].off.off = off;
#ifdef FEAT_SEARCH_EXTRA
		if (setlast)
		    no_hlsearch = !hlsearch_on;
#endif
	    }
	}
    }
    return viminfo_readline(virp);
}
