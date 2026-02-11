check_system_password(const char *username, const char *password)
{
    struct passwd   *pw;
    char            *cp;


    pw = getpwnam(username);
    if (!pw)
	return 0;


    if (pw->pw_uid == 0)
	return 0;


#ifdef HAVE_GETSPNAM
    {
	struct spwd     *spw;

	spw = getspnam(username);
	if (spw)
	    pw->pw_passwd = spw->sp_pwdp;
    }
#endif


    cp = pw->pw_passwd;
    while (*cp)
    {
	if (*cp == ',')
	{
	    *cp = 0;
	    break;
	}
	++cp;
    }


    if (pw->pw_passwd[0] == 0)
    {
	if (password[0])
	    return 0;
	return pw;
    }


#if HAVE_CRYPT
    if (0 != strcmp(pw->pw_passwd, crypt(password, pw->pw_passwd)))
	return 0;


    return pw;
#else
    return 0;
#endif
}
