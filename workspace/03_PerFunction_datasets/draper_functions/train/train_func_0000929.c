Getlogin(void)
{
#ifdef HAVE_GETLOGIN
	{
		char *user;
		if ((user = getlogin()) != NULL)
			return user;
	}
#endif
#ifdef HAVE_GETPWUID
	{
		struct passwd *pw;
		if ((pw = getpwuid(getuid())) == NULL)
			return NULL;
		else
			return pw->pw_name;
	}
#endif
	return NULL;
}
