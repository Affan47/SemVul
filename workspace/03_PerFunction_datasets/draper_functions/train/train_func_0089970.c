cavan_vfat_find_file(struct cavan_vfat_fs *fs, struct cavan_vfat_file *file, const char *pathname)
{
	struct cavan_vfat_scan_dir_walker walker;
	struct vfat_dir_entry *entry = &file->entry;
	struct cavan_vfat_find_file_context context;

	context.entry = entry;
	entry->attribute |= VFAT_ATTR_DIRECTORY;
	entry->first_cluster_hi = fs->root_first_cluster >> 16;
	entry->first_cluster_lo = fs->root_first_cluster & 0xFFFF;

	cavan_vfat_scan_dir_walker_init(&walker, &context);
	walker.entry_handler = cavan_vfat_find_file_handler;

	while (1)
	{
		int ret;
		u32 cluster;
		const char *p;

		while (*pathname == CAVAN_VFAT_PATH_SEP)
		{
			pathname++;
		}

		if (*pathname == 0)
		{
			break;
		}

		if (VFAT_IS_DIRECTORY(entry) == false)
		{
			return -EFAULT;
		}

		for (p = pathname; *p && *p != CAVAN_VFAT_PATH_SEP; p++);

		context.filename = pathname;
		context.namelen = p - pathname;
		cluster = VFAT_BUILD_START_CLUSTER(entry);
		ret = cavan_vfat_scan_dir(fs, cluster, &walker);
		if (ret != WALKER_ACTION_COMPLETE)
		{
			if (cluster > fs->root_first_cluster || context.namelen > 2 || pathname[0] != '.' || (context.namelen > 1 && pathname[1] != '.'))
			{
				return ret < 0 ? ret : -EFAULT;
			}
		}

		pathname = p;
	}

	return 0;
}
