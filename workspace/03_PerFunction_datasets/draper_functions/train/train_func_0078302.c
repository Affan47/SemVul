expand_cmdline(xp, str, col, matchcount, matches)
    expand_T	*xp;
    char_u	*str;
    int		col;
    int		*matchcount;
    char_u	***matches;
{
    char_u	*file_str = NULL;
    int		options = WILD_ADD_SLASH|WILD_SILENT;

    if (xp->xp_context == EXPAND_UNSUCCESSFUL)
    {
	beep_flush();
	return EXPAND_UNSUCCESSFUL;
    }
    if (xp->xp_context == EXPAND_NOTHING)
    {

	return EXPAND_NOTHING;
    }


    xp->xp_pattern_len = (int)(str + col - xp->xp_pattern);
    file_str = addstar(xp->xp_pattern, xp->xp_pattern_len, xp->xp_context);
    if (file_str == NULL)
	return EXPAND_UNSUCCESSFUL;

    if (p_wic)
	options += WILD_ICASE;


    if (ExpandFromContext(xp, file_str, matchcount, matches, options) == FAIL)
    {
	*matchcount = 0;
	*matches = NULL;
    }
    vim_free(file_str);

    return EXPAND_OK;
}
