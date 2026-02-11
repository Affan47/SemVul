resolve_rc_cmd(char *s, int origin)
{
	clean_line(s);

	if (*s == '#')
		return;

	if ((argcnt = parse_line(s, args)) == 0)
		return;

	if (STREQ(args[0], "set")) {
		optind = 0;
		cmd_set();
	}

	switch (origin)
	{
	case ALIAS_RCHOME:
		pc->flags |= RCHOME_IFILE;
		break;
	case ALIAS_RCLOCAL:
		pc->flags |= RCLOCAL_IFILE;
		break;
	}

	return;
}
