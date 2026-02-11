chdir_verify_path(const char *path, char *obpath)
{
	struct stat sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		if (chdir(path) == -1 || getcwd(obpath, MAXPATHLEN) == NULL) {
			warn("warning: %s", path);
			return (NULL);
		}
		return (obpath);
	}

	return (NULL);
}
