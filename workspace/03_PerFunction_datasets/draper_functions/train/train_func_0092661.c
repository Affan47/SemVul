clean_path(char *path, umode_t fmode)
{
	struct stat st;

	if (!sys_newlstat(path, &st) && (st.st_mode ^ fmode) & S_IFMT) {
		if (S_ISDIR(st.st_mode))
			sys_rmdir(path);
		else
			sys_unlink(path);
	}
}
