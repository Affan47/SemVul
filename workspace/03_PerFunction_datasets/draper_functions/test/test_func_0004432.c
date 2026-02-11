setup_edd_info(struct x86_linux_param_header *real_mode)
{
	DIR *edd_dir;
	struct dirent *cursor;
	int current_edd = 0;
	int current_mbr = 0;

	edd_dir = opendir(EDD_SYFS_DIR);
	if (!edd_dir) {
		dbgprintf(EDD_SYFS_DIR " does not exist.\n");
		return;
	}

	zero_edd(real_mode);
	while ((cursor = readdir(edd_dir))) {
		char full_dir_name[PATH_MAX];


		if (strstr(cursor->d_name, "int13_dev") != cursor->d_name)
			continue;

		snprintf(full_dir_name, PATH_MAX, "%s/%s",
				EDD_SYFS_DIR, cursor->d_name);
		full_dir_name[PATH_MAX-1] = 0;

		if (add_edd_entry(real_mode, full_dir_name, &current_edd,
					&current_mbr) != 0) {
			zero_edd(real_mode);
			goto out;
		}
	}

	real_mode->eddbuf_entries = current_edd;
	real_mode->edd_mbr_sig_buf_entries = current_mbr;

out:
	closedir(edd_dir);

	dbgprintf("Added %d EDD MBR entries and %d EDD entries.\n",
		real_mode->edd_mbr_sig_buf_entries,
		real_mode->eddbuf_entries);
}
