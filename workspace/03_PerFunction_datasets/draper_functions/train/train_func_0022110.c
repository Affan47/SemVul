skip_range(cmd, ctx)
    char_u	*cmd;
    int		*ctx;
{
    unsigned	delim;

    while (vim_strchr((char_u *)" \t0123456789.$%'/?-+,;", *cmd) != NULL)
    {
	if (*cmd == '\'')
	{
	    if (*++cmd == NUL && ctx != NULL)
		*ctx = EXPAND_NOTHING;
	}
	else if (*cmd == '/' || *cmd == '?')
	{
	    delim = *cmd++;
	    while (*cmd != NUL && *cmd != delim)
		if (*cmd++ == '\\' && *cmd != NUL)
		    ++cmd;
	    if (*cmd == NUL && ctx != NULL)
		*ctx = EXPAND_NOTHING;
	}
	if (*cmd != NUL)
	    ++cmd;
    }


    while (*cmd == ':')
	cmd = skipwhite(cmd + 1);

    return cmd;
}
