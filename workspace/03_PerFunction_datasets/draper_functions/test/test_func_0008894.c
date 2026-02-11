fwparam_sysfs_boot_info(struct boot_context *context)
{
	struct dirent *dent;
	DIR *dirfd;
	int rc = 0;

	if (!get_boot_info(context, IBFT_SYSFS_ROOT, IBFT_SUBSYS))
		return 0;


	dirfd = opendir(ISCSI_LLD_ROOT);
	if (!dirfd)
		return ISCSI_ERR_SYSFS_LOOKUP;

	while ((dent = readdir(dirfd))) {
		char lld_root[FILENAMESZ];

		memset(&lld_root, 0 , FILENAMESZ);

		if (!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
			continue;

		if (strncmp(dent->d_name, ISCSI_LLD_SUBSYS_PREFIX, 10))
			continue;

		snprintf(lld_root, FILENAMESZ, ISCSI_LLD_ROOT"%s/",
			 dent->d_name);
		if (!get_boot_info(context, lld_root, dent->d_name))
			goto done;
	}
	rc = ISCSI_ERR_NO_OBJS_FOUND;
done:
	closedir(dirfd);
	return rc;
}
