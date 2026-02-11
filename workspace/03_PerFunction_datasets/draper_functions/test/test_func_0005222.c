trx_undo_update_cleanup(

	trx_t*	trx,
	page_t*	undo_page,

	mtr_t*	mtr)
{
	trx_rseg_t*	rseg;
	trx_undo_t*	undo;

	undo = trx->update_undo;
	rseg = trx->rseg;

	ut_ad(mutex_own(&(rseg->mutex)));

	trx_purge_add_update_undo_to_history(trx, undo_page, mtr);

	UT_LIST_REMOVE(undo_list, rseg->update_undo_list, undo);

	trx->update_undo = NULL;

	if (undo->state == TRX_UNDO_CACHED) {

		UT_LIST_ADD_FIRST(undo_list, rseg->update_undo_cached, undo);
	} else {
		ut_ad(undo->state == TRX_UNDO_TO_PURGE
		      || undo->state == TRX_UNDO_TO_FREE);

		trx_undo_mem_free(undo);
	}
}
