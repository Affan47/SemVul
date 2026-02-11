cgifileopen(void)
{
	if  (user_file)
		fseek(user_file, 0L, 0);
	else  {
		char	*fn = html_inifile(UFILEN_PARAM, HTML_UFILE);
		int	fd = open(fn, O_RDWR);

		if  (fd < 0  &&  errno == ENOENT)  {
			int	oldumask = umask(007);
			fd = open(fn, O_CREAT|O_RDWR, 0660);
			umask(oldumask);
			if  (fd >= 0  &&  Effuid != Daemuid)
#ifdef	HAVE_FCHOWN
				fchown(fd, Daemuid, getegid());
#else
				chown(fn, Daemuid, getegid());
#endif
		}
		if  (fd < 0  ||  !(user_file = fdopen(fd, "r+")))  {
			html_error("Cannot open user file");
			exit(E_SETUP);
		}
		fcntl(fd, F_SETFD, 1);
		free(fn);
	}
}
