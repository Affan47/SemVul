syb_st_describe_proc(imp_sth_t *imp_sth, char *statement) {
	char *buff = my_strdup(statement);
	char *tok;

	tok = strtok(buff, " \n\t");
	if (strncasecmp(tok, "exec", 4)) {
		Safefree(buff);
		return 0;
	}
	tok = strtok(NULL, " \n\t");
	if (!tok || !*tok) {
		warn(
				"DBD::Sybase: describe_proc: didn't get a proc name in EXEC statement\n");
		Safefree(buff);
		return 0;
	}
	strcpy(imp_sth->proc, tok);
	Safefree(buff);
	return 1;
}
