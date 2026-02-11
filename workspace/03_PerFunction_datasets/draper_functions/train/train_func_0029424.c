get_homedir(void)
{
#ifndef OS_mingw32msvc
	struct passwd *pw;
	uid_t uid;
	char *homedir;
	char *username;

	homedir = getenv ("HOME");


	if ( homedir )
		return homedir;

	pw = 0;

	username = getenv("LOGNAME");
	if ( !username )
		username = getlogin();
	if ( username )
		pw = getpwnam( username);

	if ( pw == 0 ){

		uid = geteuid();
		pw = getpwuid(uid);
	}


	if ( pw )
		return pw->pw_dir;
	return 0;
#else
	return getenv("HOME");
#endif
}
