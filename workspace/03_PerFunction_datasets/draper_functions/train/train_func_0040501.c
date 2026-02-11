pfn_inject_init(void)
{
	struct dentry *dentry;

	hwpoison_dir = debugfs_create_dir("hwpoison", NULL);
	if (hwpoison_dir == NULL)
		return -ENOMEM;


	dentry = debugfs_create_file("corrupt-pfn", 0200, hwpoison_dir,
					  NULL, &hwpoison_fops);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_file("unpoison-pfn", 0200, hwpoison_dir,
				     NULL, &unpoison_fops);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u32("corrupt-filter-enable", 0600,
				    hwpoison_dir, &hwpoison_filter_enable);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u32("corrupt-filter-dev-major", 0600,
				    hwpoison_dir, &hwpoison_filter_dev_major);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u32("corrupt-filter-dev-minor", 0600,
				    hwpoison_dir, &hwpoison_filter_dev_minor);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u64("corrupt-filter-flags-mask", 0600,
				    hwpoison_dir, &hwpoison_filter_flags_mask);
	if (!dentry)
		goto fail;

	dentry = debugfs_create_u64("corrupt-filter-flags-value", 0600,
				    hwpoison_dir, &hwpoison_filter_flags_value);
	if (!dentry)
		goto fail;

#ifdef CONFIG_MEMCG
	dentry = debugfs_create_u64("corrupt-filter-memcg", 0600,
				    hwpoison_dir, &hwpoison_filter_memcg);
	if (!dentry)
		goto fail;
#endif

	return 0;
fail:
	pfn_inject_exit();
	return -ENOMEM;
}
