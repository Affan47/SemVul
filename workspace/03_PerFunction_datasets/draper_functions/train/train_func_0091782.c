row_merge_drop_temp_indexes(void)

{
	trx_t*		trx;
	btr_pcur_t	pcur;
	mtr_t		mtr;


	trx = trx_allocate_for_background();
	trx->op_info = "dropping partially created indexes";
	row_mysql_lock_data_dictionary(trx);

	mtr_start(&mtr);

	btr_pcur_open_at_index_side(
		TRUE,
		dict_table_get_first_index(dict_sys->sys_indexes),
		BTR_SEARCH_LEAF, &pcur, TRUE, &mtr);

	for (;;) {
		const rec_t*	rec;
		const byte*	field;
		ulint		len;
		table_id_t	table_id;
		dict_table_t*	table;

		btr_pcur_move_to_next_user_rec(&pcur, &mtr);

		if (!btr_pcur_is_on_user_rec(&pcur)) {
			break;
		}

		rec = btr_pcur_get_rec(&pcur);
		field = rec_get_nth_field_old(rec, DICT_SYS_INDEXES_NAME_FIELD,
					      &len);
		if (len == UNIV_SQL_NULL || len == 0
		    || (char) *field != TEMP_INDEX_PREFIX) {
			continue;
		}


		field = rec_get_nth_field_old(rec, 0, &len);
		if (len != 8) {

			continue;
		}

		table_id = mach_read_from_8(field);

		btr_pcur_store_position(&pcur, &mtr);
		btr_pcur_commit_specify_mtr(&pcur, &mtr);

		table = dict_table_get_on_id_low(table_id);

		if (table) {
			dict_index_t*	index;
			dict_index_t*	next_index;

			for (index = dict_table_get_first_index(table);
			     index; index = next_index) {

				next_index = dict_table_get_next_index(index);

				if (*index->name == TEMP_INDEX_PREFIX) {
					row_merge_drop_index(index, table, trx);
					trx_commit_for_mysql(trx);
				}
			}
		}

		mtr_start(&mtr);
		btr_pcur_restore_position(BTR_SEARCH_LEAF,
					  &pcur, &mtr);
	}

	btr_pcur_close(&pcur);
	mtr_commit(&mtr);
	row_mysql_unlock_data_dictionary(trx);
	trx_free_for_background(trx);
}
