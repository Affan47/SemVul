__writeback_inodes_sb_nr(struct super_block *sb, unsigned long nr,
				     enum wb_reason reason, bool skip_if_busy)
{
	DEFINE_WB_COMPLETION_ONSTACK(done);
	struct wb_writeback_work work = {
		.sb			= sb,
		.sync_mode		= WB_SYNC_NONE,
		.tagged_writepages	= 1,
		.done			= &done,
		.nr_pages		= nr,
		.reason			= reason,
	};
	struct backing_dev_info *bdi = sb->s_bdi;

	if (!bdi_has_dirty_io(bdi) || bdi == &noop_backing_dev_info)
		return;
	WARN_ON(!rwsem_is_locked(&sb->s_umount));

	bdi_split_work_to_wbs(sb->s_bdi, &work, skip_if_busy);
	wb_wait_for_completion(bdi, &done);
}
