get_mtab_info(void) {
	if (!have_mtab_info) {
		struct stat mtab_stat;

		var_mtab_does_not_exist = 0;
		var_mtab_is_a_symlink = 0;

		if (lstat(_PATH_MOUNTED, &mtab_stat))
			var_mtab_does_not_exist = 1;
		else if (S_ISLNK(mtab_stat.st_mode))
			var_mtab_is_a_symlink = 1;
		have_mtab_info = 1;
	}
}
