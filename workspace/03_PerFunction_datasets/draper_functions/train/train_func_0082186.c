getcaller (void)
{
#ifndef SYSTEM_GETCALLER
    static char *cache;
    struct passwd *pw;
    uid_t uid;
#endif


#ifdef AUTH_SERVER_SUPPORT
    if (CVS_Username != NULL)
	return CVS_Username;
#endif

#ifdef SYSTEM_GETCALLER
    return SYSTEM_GETCALLER ();
#else


    if (cache != NULL)
	return cache;

    uid = getuid ();
    if (uid == (uid_t) 0)
    {
	char *name;


	if (((name = getlogin ()) || (name = getenv("LOGNAME")) ||
	     (name = getenv("USER"))) && *name)
	{
	    cache = xstrdup (name);
	    return cache;
	}
    }
    if ((pw = (struct passwd *) getpwuid (uid)) == NULL)
    {
	cache = Xasprintf ("uid%lu", (unsigned long) uid);
	return cache;
    }
    cache = xstrdup (pw->pw_name);
    return cache;
#endif
}
