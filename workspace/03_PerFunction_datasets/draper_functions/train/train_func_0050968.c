map_clear(cmdp, arg, forceit, abbr)
    char_u	*cmdp;
    char_u	*arg UNUSED;
    int		forceit;
    int		abbr;
{
    int		mode;
#ifdef FEAT_LOCALMAP
    int		local;

    local = (STRCMP(arg, "<buffer>") == 0);
    if (!local && *arg != NUL)
    {
	EMSG(_(e_invarg));
	return;
    }
#endif

    mode = get_map_mode(&cmdp, forceit);
    map_clear_int(curbuf, mode,
#ifdef FEAT_LOCALMAP
	    local,
#else
	    FALSE,
#endif
	    abbr);
}
