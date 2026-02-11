dirty_one_transaction(struct super_block *s,
				 struct reiserfs_journal_list *jl)
{
	struct reiserfs_journal_cnode *cn;
	struct reiserfs_journal_list *pjl;
	int ret = 0;

	jl->j_state |= LIST_DIRTY;
	cn = jl->j_realblock;
	while (cn) {


		pjl = find_newer_jl_for_cn(cn);
		if (!pjl && cn->blocknr && cn->bh
		    && buffer_journal_dirty(cn->bh)) {
			BUG_ON(!can_dirty(cn));


			clear_buffer_journal_new(cn->bh);
			if (buffer_journal_prepared(cn->bh)) {
				set_buffer_journal_restore_dirty(cn->bh);
			} else {
				set_buffer_journal_test(cn->bh);
				mark_buffer_dirty(cn->bh);
			}
		}
		cn = cn->next;
	}
	return ret;
}
