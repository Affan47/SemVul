row_undo_ins_remove_clust_rec(

	undo_node_t*	node)
{
	btr_cur_t*	btr_cur;
	ibool		success;
	ulint		err;
	ulint		n_tries		= 0;
	mtr_t		mtr;

	mtr_start(&mtr);

	success = btr_pcur_restore_position(BTR_MODIFY_LEAF, &(node->pcur),
					    &mtr);
	ut_a(success);

	if (node->table->id == DICT_INDEXES_ID) {
		ut_ad(node->trx->dict_operation_lock_mode == RW_X_LATCH);


		dict_drop_index_tree(btr_pcur_get_rec(&(node->pcur)), &mtr);

		mtr_commit(&mtr);

		mtr_start(&mtr);

		success = btr_pcur_restore_position(BTR_MODIFY_LEAF,
						    &(node->pcur), &mtr);
		ut_a(success);
	}

	btr_cur = btr_pcur_get_btr_cur(&(node->pcur));

	success = btr_cur_optimistic_delete(btr_cur, &mtr);

	btr_pcur_commit_specify_mtr(&(node->pcur), &mtr);

	if (success) {
		trx_undo_rec_release(node->trx, node->undo_no);

		return(DB_SUCCESS);
	}
retry:

	mtr_start(&mtr);

	success = btr_pcur_restore_position(BTR_MODIFY_TREE,
					    &(node->pcur), &mtr);
	ut_a(success);

	btr_cur_pessimistic_delete(&err, FALSE, btr_cur,
				   trx_is_recv(node->trx)
				   ? RB_RECOVERY
				   : RB_NORMAL, &mtr);


	if (err == DB_OUT_OF_FILE_SPACE
	    && n_tries < BTR_CUR_RETRY_DELETE_N_TIMES) {

		btr_pcur_commit_specify_mtr(&(node->pcur), &mtr);

		n_tries++;

		os_thread_sleep(BTR_CUR_RETRY_SLEEP_TIME);

		goto retry;
	}

	btr_pcur_commit_specify_mtr(&(node->pcur), &mtr);

	trx_undo_rec_release(node->trx, node->undo_no);

	return(err);
}
