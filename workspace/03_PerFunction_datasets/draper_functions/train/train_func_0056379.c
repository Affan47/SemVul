chirp_acl_init_copy(const char *path)
{
	char oldpath[CHIRP_LINE_MAX];
	char newpath[CHIRP_LINE_MAX];
	char subject[CHIRP_LINE_MAX];
	CHIRP_FILE *oldfile;
	CHIRP_FILE *newfile;
	int result = 0;
	int flags;

	if(!cfs->do_acl_check())
		return 1;

	sprintf(oldpath, "%s/..", path);
	sprintf(newpath, "%s/%s", path, CHIRP_ACL_BASE_NAME);

	oldfile = chirp_acl_open(oldpath);
	if(oldfile) {
		newfile = cfs_fopen(newpath, "w");
		if(newfile) {
			while(chirp_acl_read(oldfile, subject, &flags)) {
				cfs_fprintf(newfile, "%s %s\n", subject, chirp_acl_flags_to_text(flags));
			}
			cfs_fclose(newfile);
			result = 1;
		}
		chirp_acl_close(oldfile);
	}

	return result;
}
