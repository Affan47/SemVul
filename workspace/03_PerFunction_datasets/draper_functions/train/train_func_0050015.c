find_block_device_in_dir(struct arena *ap)
{
	DIR *dir;
	struct dirent *entry;
	char *retpath = NULL;
	int len, rem;

	len = strlen(ap->devpath);
	rem = DEVNAME_MAX-2 - len;
	if (rem <= 0)
		return NULL;

	dir = opendir(ap->devpath);
	if (!dir)
		return NULL;

	ap->devpath[len++] = '/';

	while ((entry = readdir(dir)) != NULL) {
		safe_strncpy(ap->devpath + len, entry->d_name, rem);

		if (lstat(ap->devpath, &ap->st) != 0)
			continue;
		if (S_ISBLK(ap->st.st_mode) && ap->st.st_rdev == ap->dev) {
			retpath = xstrdup(ap->devpath);
			break;
		}
		if (S_ISDIR(ap->st.st_mode)) {

			if (DOT_OR_DOTDOT(entry->d_name))
				continue;
			retpath = find_block_device_in_dir(ap);
			if (retpath)
				break;
		}
	}
	closedir(dir);

	return retpath;
}
