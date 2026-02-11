is_mounted(const char *mount_dir)
{
	struct mntent *m;
	FILE *f = setmntent("/etc/mtab", "r");
 	char *mount_dir_expanded, *mnt_dir_expanded;

	if (!(mount_dir_expanded = realpath(mount_dir, NULL)))
		return false;

	while(m = getmntent(f)) {
 	        if(mnt_dir_expanded = realpath(m->mnt_dir, NULL)) {
			if (strcmp(mount_dir_expanded, mnt_dir_expanded)==0) {
				free(mnt_dir_expanded);
				free(mount_dir_expanded);
				return true;
			}
			free(mnt_dir_expanded);
		}
	}
	free(mount_dir_expanded);
	return false;
}
