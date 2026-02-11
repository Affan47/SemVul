jbd2_journal_bmap(journal_t *journal, unsigned long blocknr,
		 unsigned long long *retp)
{
	int err = 0;
	unsigned long long ret;

	if (journal->j_inode) {
		ret = bmap(journal->j_inode, blocknr);
		if (ret)
			*retp = ret;
		else {
			printk(KERN_ALERT "%s: journal block not found "
					"at offset %lu on %s\n",
			       __func__, blocknr, journal->j_devname);
			err = -EIO;
			__journal_abort_soft(journal, err);
		}
	} else {
		*retp = blocknr;
	}
	return err;
}
