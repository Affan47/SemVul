get_user_name(const char *progname)
{
#ifndef WIN32
	struct passwd *pw;

	pw = getpwuid(geteuid());
	if (!pw)
	{
		fprintf(stderr, _("%s: could not obtain information about current user: %s\n"),
				progname, strerror(errno));
		exit(1);
	}
	return pw->pw_name;
#else
	static char username[128];
	DWORD		len = sizeof(username) - 1;

	if (!GetUserName(username, &len))
	{
		fprintf(stderr, _("%s: could not get current user name: %s\n"),
				progname, strerror(errno));
		exit(1);
	}
	return username;
#endif
}
