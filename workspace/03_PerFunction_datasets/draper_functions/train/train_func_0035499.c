ap_session_running(int session)
{
	struct stat statbuf;
	struct passwd *pwd;
	char path[1024];

	pwd = getpwuid(geteuid());

	sprintf(path, "/tmp/alsaplayer_%s_%d", pwd == NULL ? "anonymous" :
			pwd->pw_name, session);
	if (stat(path, &statbuf) != 0)
		return 0;
	if (S_ISSOCK(statbuf.st_mode)) {
		if (ap_ping(session))
			return 1;
	}
	return 0;
}
