f2fs_issue_flush(struct f2fs_sb_info *sbi)
{
	struct flush_cmd_control *fcc = SM_I(sbi)->cmd_control_info;
	struct flush_cmd cmd;

	trace_f2fs_issue_flush(sbi->sb, test_opt(sbi, NOBARRIER),
					test_opt(sbi, FLUSH_MERGE));

	if (test_opt(sbi, NOBARRIER))
		return 0;

	if (!test_opt(sbi, FLUSH_MERGE)) {
		struct bio *bio = f2fs_bio_alloc(0);
		int ret;

		bio->bi_bdev = sbi->sb->s_bdev;
		ret = submit_bio_wait(WRITE_FLUSH, bio);
		bio_put(bio);
		return ret;
	}

	init_completion(&cmd.wait);

	llist_add(&cmd.llnode, &fcc->issue_list);

	if (!fcc->dispatch_list)
		wake_up(&fcc->flush_wait_queue);

	wait_for_completion(&cmd.wait);

	return cmd.ret;
}
