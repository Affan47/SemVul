set_user(FILE *fd, const char *user) {
	struct passwd *pw;

	pw = getpwnam(user);
	if (pw == NULL) {
		errno = EINVAL;
		return (-1);
	}
	return (fchown(fileno(fd), pw->pw_uid, -1));
}
