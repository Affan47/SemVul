do_check(char *path, uid_t uid, gid_t gid, mode_t mode, int file)
{
	struct stat st;
	int fd;

	if (stat(path, &st)) {
		if (file) {
			einfo("%s: creating file", path);
			if (!mode)
				mode = S_IRUSR | S_IWUSR | S_IRGRP |
				    S_IWGRP | S_IROTH;
			if ((fd = open(path, O_CREAT, mode)) == -1) {
				eerror("%s: open: %s", applet, strerror(errno));
				return -1;
			}
			close (fd);
		} else {
			einfo("%s: creating directory", path);
			if (!mode)
				mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;
			if (mkdir(path, mode)) {
				eerror("%s: mkdir: %s", applet,
				    strerror (errno));
				return -1;
			}
			mode = 0;
		}
	} else {
		if ((file && S_ISDIR(st.st_mode)) ||
		    (!file && !S_ISDIR(st.st_mode)))
		{
			if (file)
				eerror("%s: is a directory", path);
			else
				eerror("%s: is a file", path);
			return -1;
		}
	}

	if (mode && (st.st_mode & 0777) != mode) {
		einfo("%s: correcting mode", applet);
		if (chmod(path, mode)) {
			eerror("%s: chmod: %s", applet, strerror(errno));
			return -1;
		}
	}

	if (st.st_uid != uid || st.st_gid != gid) {
		if (st.st_dev || st.st_ino)
			einfo("%s: correcting owner", path);
		if (chown(path, uid, gid)) {
			eerror("%s: chown: %s", applet, strerror(errno));
			return -1;
		}
	}

	return 0;
}
