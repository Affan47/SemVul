delayed_free(struct rcu_head *p)
{
	struct msdos_sb_info *sbi = container_of(p, struct msdos_sb_info, rcu);
	unload_nls(sbi->nls_disk);
	unload_nls(sbi->nls_io);
	if (sbi->options.iocharset != fat_default_iocharset)
		kfree(sbi->options.iocharset);
	kfree(sbi);
}
