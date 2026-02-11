row_sel_fetch_columns(

	dict_index_t*	index,
	const rec_t*	rec,

	const ulint*	offsets,
	sym_node_t*	column)

{
	dfield_t*	val;
	ulint		index_type;
	ulint		field_no;
	const byte*	data;
	ulint		len;

	ut_ad(rec_offs_validate(rec, index, offsets));

	if (dict_index_is_clust(index)) {
		index_type = SYM_CLUST_FIELD_NO;
	} else {
		index_type = SYM_SEC_FIELD_NO;
	}

	while (column) {
		mem_heap_t*	heap = NULL;
		ibool		needs_copy;

		field_no = column->field_nos[index_type];

		if (field_no != ULINT_UNDEFINED) {

			if (UNIV_UNLIKELY(rec_offs_nth_extern(offsets,
							      field_no))) {


				heap = mem_heap_create(1);

				data = btr_rec_copy_externally_stored_field(
					rec, offsets,
					dict_table_zip_size(index->table),
					field_no, &len, heap);


				ut_a(data);
				ut_a(len != UNIV_SQL_NULL);

				needs_copy = TRUE;
			} else {
				data = rec_get_nth_field(rec, offsets,
							 field_no, &len);

				needs_copy = column->copy_val;
			}

			if (needs_copy) {
				eval_node_copy_and_alloc_val(column, data,
							     len);
			} else {
				val = que_node_get_val(column);
				dfield_set_data(val, data, len);
			}

			if (UNIV_LIKELY_NULL(heap)) {
				mem_heap_free(heap);
			}
		}

		column = UT_LIST_GET_NEXT(col_var_list, column);
	}
}
