trx_undo_insert_cleanup(

	trx_t*	trx)
{
	trx_undo_t*	undo;
	trx_rseg_t*	rseg;

	undo = trx->insert_undo;
	ut_ad(undo);

	rseg = trx->rseg;

	mutex_enter(&(rseg->mutex));

	UT_LIST_REMOVE(undo_list, rseg->insert_undo_list, undo);
	trx->insert_undo = NULL;

	if (undo->state == TRX_UNDO_CACHED) {

		UT_LIST_ADD_FIRST(undo_list, rseg->insert_undo_cached, undo);
	} else {
		ut_ad(undo->state == TRX_UNDO_TO_FREE);


		mutex_exit(&(rseg->mutex));

		trx_undo_seg_free(undo);

		mutex_enter(&(rseg->mutex));

		ut_ad(rseg->curr_size > undo->size);

		rseg->curr_size -= undo->size;

		trx_undo_mem_free(undo);
	}

	mutex_exit(&(rseg->mutex));
}
