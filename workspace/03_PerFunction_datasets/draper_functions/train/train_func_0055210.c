parse_options(char *options, struct omfs_sb_info *sbi)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int option;

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_uid:
			if (match_int(&args[0], &option))
				return 0;
			sbi->s_uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(sbi->s_uid))
				return 0;
			break;
		case Opt_gid:
			if (match_int(&args[0], &option))
				return 0;
			sbi->s_gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(sbi->s_gid))
				return 0;
			break;
		case Opt_umask:
			if (match_octal(&args[0], &option))
				return 0;
			sbi->s_fmask = sbi->s_dmask = option;
			break;
		case Opt_dmask:
			if (match_octal(&args[0], &option))
				return 0;
			sbi->s_dmask = option;
			break;
		case Opt_fmask:
			if (match_octal(&args[0], &option))
				return 0;
			sbi->s_fmask = option;
			break;
		default:
			return 0;
		}
	}
	return 1;
}
