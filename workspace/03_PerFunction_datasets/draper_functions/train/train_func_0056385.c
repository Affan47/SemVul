jbd2_journal_cancel_revoke(handle_t *handle, struct journal_head *jh)
{
	struct jbd2_revoke_record_s *record;
	journal_t *journal = handle->h_transaction->t_journal;
	int need_cancel;
	int did_revoke = 0;
	struct buffer_head *bh = jh2bh(jh);

	jbd_debug(4, "journal_head %p, cancelling revoke\n", jh);


	if (test_set_buffer_revokevalid(bh)) {
		need_cancel = test_clear_buffer_revoked(bh);
	} else {
		need_cancel = 1;
		clear_buffer_revoked(bh);
	}

	if (need_cancel) {
		record = find_revoke_record(journal, bh->b_blocknr);
		if (record) {
			jbd_debug(4, "cancelled existing revoke on "
				  "blocknr %llu\n", (unsigned long long)bh->b_blocknr);
			spin_lock(&journal->j_revoke_lock);
			list_del(&record->hash);
			spin_unlock(&journal->j_revoke_lock);
			kmem_cache_free(jbd2_revoke_record_cache, record);
			did_revoke = 1;
		}
	}

#ifdef JBD2_EXPENSIVE_CHECKING

	record = find_revoke_record(journal, bh->b_blocknr);
	J_ASSERT_JH(jh, record == NULL);
#endif


	if (need_cancel) {
		struct buffer_head *bh2;
		bh2 = __find_get_block(bh->b_bdev, bh->b_blocknr, bh->b_size);
		if (bh2) {
			if (bh2 != bh)
				clear_buffer_revoked(bh2);
			__brelse(bh2);
		}
	}
	return did_revoke;
}
