journal_skip_recovery(journal_t *journal)
{
	int			err;
	journal_superblock_t *	sb;

	struct recovery_info	info;

	memset (&info, 0, sizeof(info));
	sb = journal->j_superblock;

	err = do_one_pass(journal, &info, PASS_SCAN);

	if (err) {
		printk(KERN_ERR "JBD: error %d scanning journal\n", err);
		++journal->j_transaction_sequence;
	} else {
#ifdef CONFIG_JBD_DEBUG
		int dropped = info.end_transaction - be32_to_cpu(sb->s_sequence);
#endif
		jbd_debug(1,
			  "JBD: ignoring %d transaction%s from the journal.\n",
			  dropped, (dropped == 1) ? "" : "s");
		journal->j_transaction_sequence = ++info.end_transaction;
	}

	journal->j_tail = 0;
	return err;
}
