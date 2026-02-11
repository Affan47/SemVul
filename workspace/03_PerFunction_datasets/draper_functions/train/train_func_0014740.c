init_romfs_fs(void)
{
	int ret;

	pr_info("ROMFS MTD (C) 2007 Red Hat, Inc.\n");

	romfs_inode_cachep =
		kmem_cache_create("romfs_i",
				  sizeof(struct romfs_inode_info), 0,
				  SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD,
				  romfs_i_init_once);

	if (!romfs_inode_cachep) {
		pr_err("Failed to initialise inode cache\n");
		return -ENOMEM;
	}
	ret = register_filesystem(&romfs_fs_type);
	if (ret) {
		pr_err("Failed to register filesystem\n");
		goto error_register;
	}
	return 0;

error_register:
	kmem_cache_destroy(romfs_inode_cachep);
	return ret;
}
