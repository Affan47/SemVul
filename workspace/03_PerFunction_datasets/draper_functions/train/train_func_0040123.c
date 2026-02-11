set_user(void)
{
#if	!defined(_WIN32)
int		rc;
struct passwd	*pwd = NULL;

    if ( (pwd = getpwnam(oops_user)) != 0 ) {
	rc = setgid(pwd->pw_gid);
	if ( rc == -1 )
	    verb_printf("set_user(): Can't setgid(): %m\n");
        else
            oops_uid = pwd->pw_uid;

#if	defined(LINUX)


	rc = seteuid(pwd->pw_uid);
#else
	rc = setuid(pwd->pw_uid);
#endif
	if ( rc == -1 )
	    verb_printf("set_user(): Can't setuid(): %m\n");
    } else
	printf("set_user(): Can't getpwnam() `%s'.\n", oops_user);
#endif
}
