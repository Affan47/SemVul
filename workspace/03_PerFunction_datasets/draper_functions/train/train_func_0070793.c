get_backup_name(const char *fname)
{
	if (backup_dir) {

		if (copy_valid_path(fname))
			return backup_dir_buf;

		return NULL;
	}

	if (stringjoin(backup_dir_buf, MAXPATHLEN, fname, backup_suffix, NULL) < MAXPATHLEN)
		return backup_dir_buf;

	rprintf(FERROR, "backup filename too long\n");
	return NULL;
}
