setup_ident(void)
{
	struct passwd *pw = NULL;


	if (!git_default_name[0]) {
		pw = getpwuid(getuid());
		if (!pw)
			die("You don't exist. Go away!");
		copy_gecos(pw, git_default_name, sizeof(git_default_name));
	}

	if (!git_default_email[0]) {
		if (!pw)
			pw = getpwuid(getuid());
		if (!pw)
			die("You don't exist. Go away!");
		copy_email(pw);
	}


	if (!git_default_date[0])
		datestamp(git_default_date, sizeof(git_default_date));
}
