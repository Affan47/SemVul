logfs_make_writeable(struct super_block *sb)
{
	int err;

	err = logfs_open_segfile(sb);
	if (err)
		return err;


	err = logfs_recover_sb(sb);
	if (err)
		return err;


	err = logfs_check_areas(sb);
	if (err)
		return err;


	logfs_gc_pass(sb);


	err = logfs_replay_journal(sb);
	if (err)
		return err;

	return 0;
}
