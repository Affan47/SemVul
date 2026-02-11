OpenDefaultFile(char *mode)
{


	FILE           *setfile;
	char           *home;
	char            filename[PATH_MAX];
	if (save_filename == NULL) {
		home = getenv("HOME");
		if (home && ((strlen(home) + strlen(AUMIXRC) + 2) < PATH_MAX)) {
			sprintf(filename, "%s/.%s", home, AUMIXRC);
			setfile = CheckAndOpen(filename, mode);
		}
		if (setfile == NULL) {
			if ((strlen(AUMIXRC_PATH) + strlen(AUMIXRC) + 1) < PATH_MAX) {
				sprintf(filename, "%s/%s", AUMIXRC_PATH, AUMIXRC);
				setfile = CheckAndOpen(filename, mode);
			}
		}
		if (setfile == NULL) {
			return NULL;
		}
	} else
		setfile = CheckAndOpen(save_filename, mode);
	return setfile;
}
