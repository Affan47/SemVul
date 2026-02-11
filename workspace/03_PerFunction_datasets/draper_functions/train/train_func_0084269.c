ap_find_session(char *session_name, int *session)
{
	char remote_name[AP_SESSION_MAX];
	char test_path[1024];
	char tmp[1024];
	char username[512];
	struct passwd *pwd;
	DIR *dir;
	struct dirent *entry;
	int session_id=0;

	if (!session_name)
		return 0;
	dir = opendir("/tmp");

	pwd = getpwuid(geteuid());

	sprintf(username, "%s", pwd == NULL ? "anonymous" : pwd->pw_name);

	sprintf(test_path, "alsaplayer_%s_", username);

	if (dir) {
		while ((entry = readdir(dir)) != NULL) {
			if (strncmp(entry->d_name, test_path, strlen(test_path)) == 0) {
				sprintf(tmp, "%s%%d", test_path);
				if (sscanf(entry->d_name, tmp, &session_id) == 1) {
					if (ap_session_running(session_id) == 1) {
						if (ap_get_session_name(session_id, remote_name)) {
							if (strcmp(remote_name, session_name) == 0) {
								*session = session_id;
								closedir(dir);
								return 1;
							}
						}
					}
				}
			}
		}
		closedir(dir);
	}
	return 0;
}
