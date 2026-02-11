setflag(char *buf, char *name, int id, char *args, struct adsi_script *state, const char *script, int lineno)
{
	char *tok = get_token(&args, script, lineno);
	char sname[80];
	struct adsi_flag *flag;

	if (!tok) {
		ast_log(LOG_WARNING, "Setting flag requires a flag number at line %d of %s\n", lineno, script);
		return 0;
	}

	if (process_token(sname, tok, sizeof(sname) - 1, ARG_STRING)) {
		ast_log(LOG_WARNING, "Invalid flag '%s' at line %d of %s\n", tok, lineno, script);
		return 0;
	}

	if (!(flag = getflagbyname(state, sname, script, lineno, 0))) {
		ast_log(LOG_WARNING, "Flag '%s' is undeclared at line %d of %s\n", sname, lineno, script);
		return 0;
	}

	buf[0] = id;
	buf[1] = ((flag->id & 0x7) << 4) | 1;

	return 2;
}
