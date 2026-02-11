ibuf_build_entry_from_ibuf_rec_func(

#ifdef UNIV_DEBUG
	mtr_t*		mtr,
#endif
	const rec_t*	ibuf_rec,
	mem_heap_t*	heap,
	dict_index_t**	pindex)

{
	dtuple_t*	tuple;
	dfield_t*	field;
	ulint		n_fields;
	const byte*	types;
	const byte*	data;
	ulint		len;
	ulint		info_len;
	ulint		i;
	ulint		comp;
	dict_index_t*	index;

	ut_ad(mtr_memo_contains_page(mtr, ibuf_rec, MTR_MEMO_PAGE_X_FIX)
	      || mtr_memo_contains_page(mtr, ibuf_rec, MTR_MEMO_PAGE_S_FIX));
	ut_ad(ibuf_inside(mtr));

	data = rec_get_nth_field_old(ibuf_rec, IBUF_REC_FIELD_MARKER, &len);

	if (len > 1) {


		return(ibuf_build_entry_pre_4_1_x(ibuf_rec, heap, pindex));
	}


	ut_a(trx_sys_multiple_tablespace_format);
	ut_a(*data == 0);
	ut_a(rec_get_n_fields_old(ibuf_rec) > IBUF_REC_FIELD_USER);

	n_fields = rec_get_n_fields_old(ibuf_rec) - IBUF_REC_FIELD_USER;

	tuple = dtuple_create(heap, n_fields);

	types = rec_get_nth_field_old(ibuf_rec, IBUF_REC_FIELD_METADATA, &len);

	ibuf_rec_get_info(mtr, ibuf_rec, NULL, &comp, &info_len, NULL);

	index = ibuf_dummy_index_create(n_fields, comp);

	len -= info_len;
	types += info_len;

	ut_a(len == n_fields * DATA_NEW_ORDER_NULL_TYPE_BUF_SIZE);

	for (i = 0; i < n_fields; i++) {
		field = dtuple_get_nth_field(tuple, i);

		data = rec_get_nth_field_old(
			ibuf_rec, i + IBUF_REC_FIELD_USER, &len);

		dfield_set_data(field, data, len);

		dtype_new_read_for_order_and_null_size(
			dfield_get_type(field),
			types + i * DATA_NEW_ORDER_NULL_TYPE_BUF_SIZE);

		ibuf_dummy_index_add_col(index, dfield_get_type(field), len);
	}


	ut_d(dict_table_add_system_columns(index->table, index->table->heap));

	*pindex = index;

	return(tuple);
}
