lock_sec_rec_cons_read_sees(

	const rec_t*		rec,


	const read_view_t*	view)
{
	trx_id_t	max_trx_id;

	ut_ad(page_rec_is_user_rec(rec));


	if (recv_recovery_is_on()) {

		return(FALSE);
	}

	max_trx_id = page_get_max_trx_id(page_align(rec));
	ut_ad(max_trx_id);

	return(max_trx_id < view->up_limit_id);
}
