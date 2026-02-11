blkid__scan_dir(char *dirname, dev_t devno, struct dir_list **list,
		     char **devname)
{
	DIR	*dir;
	struct dirent *dp;
	char	path[1024];
	int	dirlen;
	struct stat st;

	if ((dir = opendir(dirname)) == NULL)
		return;
	dirlen = strlen(dirname) + 2;
	while ((dp = readdir(dir)) != 0) {
		if (dirlen + strlen(dp->d_name) >= sizeof(path))
			continue;

		if (dp->d_name[0] == '.' &&
		    ((dp->d_name[1] == 0) ||
		     ((dp->d_name[1] == '.') && (dp->d_name[2] == 0))))
			continue;

		sprintf(path, "%s/%s", dirname, dp->d_name);
		if (stat(path, &st) < 0)
			continue;

		if (S_ISBLK(st.st_mode) && st.st_rdev == devno) {
			*devname = blkid_strdup(path);
			DBG(DEBUG_DEVNO,
			    printf("found 0x%llx at %s (%p)\n", (long long)devno,
				   path, *devname));
			break;
		}
		if (list && S_ISDIR(st.st_mode) && !lstat(path, &st) &&
		    S_ISDIR(st.st_mode))
			add_to_dirlist(path, list);
	}
	closedir(dir);
	return;
}
