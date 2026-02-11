run_command_stream(
	cond_rc_t *cond_rc, FILE *f, const exec_context_t *exc)
{
	char *tline;
	char line[1024];


	fcntl(fileno(f), F_SETFD, 1);


	handle_all_expose();

	tline = fgets(line, (sizeof line) - 1, f);
	while (tline)
	{
		int l;
		while (tline && (l = strlen(line)) < sizeof(line) && l >= 2 &&
		      line[l-2]=='\\' && line[l-1]=='\n')
		{
			tline = fgets(line+l-2,sizeof(line)-l+1,f);
		}
		tline=line;
		while (isspace((unsigned char)*tline))
		{
			tline++;
		}
		l = strlen(tline);
		if (l > 0 && tline[l - 1] == '\n')
		{
			tline[l - 1] = '\0';
		}
		execute_function(cond_rc, exc, tline, 0);
		tline = fgets(line, (sizeof line) - 1, f);
	}

	return;
}
