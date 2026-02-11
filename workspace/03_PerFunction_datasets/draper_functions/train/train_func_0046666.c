dict_close(void)

{
	ulint	i;


	for (i = 0; i < hash_get_n_cells(dict_sys->table_hash); i++) {
		dict_table_t*	table;

		table = HASH_GET_FIRST(dict_sys->table_hash, i);

		while (table) {
			dict_table_t*	prev_table = table;

			table = HASH_GET_NEXT(name_hash, prev_table);
#ifdef UNIV_DEBUG
			ut_a(prev_table->magic_n == DICT_TABLE_MAGIC_N);
#endif

			mutex_enter(&dict_sys->mutex);

			dict_table_remove_from_cache(prev_table);

			mutex_exit(&dict_sys->mutex);
		}
	}

	hash_table_free(dict_sys->table_hash);


	hash_table_free(dict_sys->table_id_hash);

	dict_ind_free();

	mutex_free(&dict_sys->mutex);

	rw_lock_free(&dict_operation_lock);
	memset(&dict_operation_lock, 0x0, sizeof(dict_operation_lock));

	mutex_free(&dict_foreign_err_mutex);

	mem_free(dict_sys);
	dict_sys = NULL;

	for (i = 0; i < DICT_TABLE_STATS_LATCHES_SIZE; i++) {
		rw_lock_free(&dict_table_stats_latches[i]);
	}
}
