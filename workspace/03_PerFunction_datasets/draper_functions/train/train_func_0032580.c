jbd2_journal_get_create_access(handle_t *handle, struct buffer_head *bh)
{
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	struct journal_head *jh = jbd2_journal_add_journal_head(bh);
	int err;

	jbd_debug(5, "journal_head %p\n", jh);
	err = -EROFS;
	if (is_handle_aborted(handle))
		goto out;
	journal = transaction->t_journal;
	err = 0;

	JBUFFER_TRACE(jh, "entry");


	jbd_lock_bh_state(bh);
	J_ASSERT_JH(jh, (jh->b_transaction == transaction ||
		jh->b_transaction == NULL ||
		(jh->b_transaction == journal->j_committing_transaction &&
			  jh->b_jlist == BJ_Forget)));

	J_ASSERT_JH(jh, jh->b_next_transaction == NULL);
	J_ASSERT_JH(jh, buffer_locked(jh2bh(jh)));

	if (jh->b_transaction == NULL) {


		clear_buffer_dirty(jh2bh(jh));

		jh->b_modified = 0;

		JBUFFER_TRACE(jh, "file as BJ_Reserved");
		spin_lock(&journal->j_list_lock);
		__jbd2_journal_file_buffer(jh, transaction, BJ_Reserved);
		spin_unlock(&journal->j_list_lock);
	} else if (jh->b_transaction == journal->j_committing_transaction) {

		jh->b_modified = 0;

		JBUFFER_TRACE(jh, "set next transaction");
		spin_lock(&journal->j_list_lock);
		jh->b_next_transaction = transaction;
		spin_unlock(&journal->j_list_lock);
	}
	jbd_unlock_bh_state(bh);


	JBUFFER_TRACE(jh, "cancelling revoke");
	jbd2_journal_cancel_revoke(handle, jh);
out:
	jbd2_journal_put_journal_head(jh);
	return err;
}
