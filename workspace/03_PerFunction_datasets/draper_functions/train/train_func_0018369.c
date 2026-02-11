jbd2_cleanup_journal_tail(journal_t *journal)
{
	tid_t		first_tid;
	unsigned long	blocknr;

	if (is_journal_aborted(journal))
		return -EIO;

	if (!jbd2_journal_get_log_tail(journal, &first_tid, &blocknr))
		return 1;
	J_ASSERT(blocknr != 0);


	if (journal->j_flags & JBD2_BARRIER)
		blkdev_issue_flush(journal->j_fs_dev, GFP_NOFS, NULL);

	return __jbd2_update_log_tail(journal, first_tid, blocknr);
}
