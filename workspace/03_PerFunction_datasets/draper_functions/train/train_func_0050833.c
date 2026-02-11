cleantmp(const char *name)
{
	struct stat	st;
	DIR	*dirfd;
	struct dirent	*dp;
	char	*fn = NULL;
	size_t	fnsz = 0, ssz;
	time_t	now;

	if ((dirfd = opendir("tmp")) == NULL)
		return;
	time(&now);
	while ((dp = readdir(dirfd)) != NULL) {
		if (dp->d_name[0] == '.' &&
				(dp->d_name[1] == '\0' ||
				 (dp->d_name[1] == '.' &&
				  dp->d_name[2] == '\0')))
			continue;
		if (dp->d_name[0] == '.')
			continue;
		if ((ssz = strlen(dp->d_name)) + 5 > fnsz) {
			free(fn);
			fn = smalloc(fnsz = ssz + 40);
		}
		strcpy(fn, "tmp/");
		strcpy(&fn[4], dp->d_name);
		if (stat(fn, &st) < 0)
			continue;
		if (st.st_atime + 36*3600 < now)
			unlink(fn);
	}
	free(fn);
	closedir(dirfd);
}
