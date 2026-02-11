get_set_pwd(void)
{
	PG_CMD_DECL;

	char	   *pwd1,
			   *pwd2;
	char		pwdpath[MAXPGPATH];
	struct stat statbuf;

	if (pwprompt)
	{


		pwd1 = simple_prompt("Enter new superuser password: ", 100, false);
		pwd2 = simple_prompt("Enter it again: ", 100, false);
		if (strcmp(pwd1, pwd2) != 0)
		{
			fprintf(stderr, _("Passwords didn't match.\n"));
			exit_nicely();
		}
		free(pwd2);
	}
	else
	{


		FILE	   *pwf = fopen(pwfilename, "r");
		char		pwdbuf[MAXPGPATH];
		int			i;

		if (!pwf)
		{
			fprintf(stderr, _("%s: could not open file \"%s\" for reading: %s\n"),
					progname, pwfilename, strerror(errno));
			exit_nicely();
		}
		if (!fgets(pwdbuf, sizeof(pwdbuf), pwf))
		{
			fprintf(stderr, _("%s: could not read password from file \"%s\": %s\n"),
					progname, pwfilename, strerror(errno));
			exit_nicely();
		}
		fclose(pwf);

		i = strlen(pwdbuf);
		while (i > 0 && (pwdbuf[i - 1] == '\r' || pwdbuf[i - 1] == '\n'))
			pwdbuf[--i] = '\0';

		pwd1 = xstrdup(pwdbuf);

	}
	printf(_("setting password ... "));
	fflush(stdout);

	snprintf(cmd, sizeof(cmd),
			 "\"%s\" %s template1 >%s",
			 backend_exec, backend_options,
			 DEVNULL);

	PG_CMD_OPEN;

	PG_CMD_PRINTF2("ALTER USER \"%s\" WITH PASSWORD E'%s';\n",
				   username, escape_quotes(pwd1));


	free(pwd1);

	PG_CMD_CLOSE;

	check_ok();

	snprintf(pwdpath, sizeof(pwdpath), "%s/global/pg_auth", pg_data);
	if (stat(pwdpath, &statbuf) != 0 || !S_ISREG(statbuf.st_mode))
	{
		fprintf(stderr,
				_("%s: The password file was not generated. "
				  "Please report this problem.\n"),
				progname);
		exit_nicely();
	}
}
