nilfs_transaction_lock(struct super_block *sb,
				   struct nilfs_transaction_info *ti,
				   int gcflag)
{
	struct nilfs_transaction_info *cur_ti = current->journal_info;
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_sc_info *sci = nilfs->ns_writer;

	WARN_ON(cur_ti);
	ti->ti_flags = NILFS_TI_WRITER;
	ti->ti_count = 0;
	ti->ti_save = cur_ti;
	ti->ti_magic = NILFS_TI_MAGIC;
	current->journal_info = ti;

	for (;;) {
		trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_TRYLOCK);

		down_write(&nilfs->ns_segctor_sem);
		if (!test_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags))
			break;

		nilfs_segctor_do_immediate_flush(sci);

		up_write(&nilfs->ns_segctor_sem);
		yield();
	}
	if (gcflag)
		ti->ti_flags |= NILFS_TI_GC;

	trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_LOCK);
}
