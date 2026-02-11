matchdir(pattern)
	char *pattern;
{
	struct stat stb;
	struct dirent *dp;
	DIR *dirp;

	dirp = opendir(gpath[0] == '\0' ? "." : gpath);
	if (dirp == NULL) {
		if (globbed)
			return;
		goto patherr2;
	}
	if (fstat(dirfd(dirp), &stb) < 0)
		goto patherr1;
	if (!isdir(stb)) {
		errno = ENOTDIR;
		goto patherr1;
	}
	while ((dp = readdir(dirp)) != NULL) {
		if (dp->d_ino == 0)
			continue;
		if (match(dp->d_name, pattern)) {
			Gcat(gpath, dp->d_name);
			globcnt++;
		}
	}
	closedir(dirp);
	return;

patherr1:
	closedir(dirp);
patherr2:
	globerr = "Bad directory components";
}
