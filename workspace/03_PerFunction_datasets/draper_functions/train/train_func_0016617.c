trx_i_s_create_lock_id(

	const i_s_locks_row_t*	row,
	char*			lock_id,
	ulint			lock_id_size)

{
	int	res_len;


	if (row->lock_space != ULINT_UNDEFINED) {

		res_len = ut_snprintf(lock_id, lock_id_size,
				      TRX_ID_FMT ":%lu:%lu:%lu",
				      row->lock_trx_id, row->lock_space,
				      row->lock_page, row->lock_rec);
	} else {

		res_len = ut_snprintf(lock_id, lock_id_size,
				      TRX_ID_FMT ":%llu",
				      row->lock_trx_id,
				      row->lock_table_id);
	}


	ut_a(res_len >= 0);
	ut_a((ulint) res_len < lock_id_size);

	return(lock_id);
}
