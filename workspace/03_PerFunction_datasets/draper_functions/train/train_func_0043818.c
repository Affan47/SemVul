row_sel_store_mysql_rec(

	byte*		mysql_rec,
	row_prebuilt_t*	prebuilt,
	const rec_t*	rec,


	ibool		rec_clust,


	const ulint*	offsets)

{
	mem_heap_t*	extern_field_heap	= NULL;
	mem_heap_t*	heap;
	ulint		i;

	ut_ad(prebuilt->mysql_template);
	ut_ad(prebuilt->default_rec);
	ut_ad(rec_offs_validate(rec, NULL, offsets));
	ut_ad(!rec_get_deleted_flag(rec, rec_offs_comp(offsets)));

	if (UNIV_LIKELY_NULL(prebuilt->blob_heap)) {
		mem_heap_free(prebuilt->blob_heap);
		prebuilt->blob_heap = NULL;
	}

	for (i = 0; i < prebuilt->n_template; i++) {

		const mysql_row_templ_t*templ = prebuilt->mysql_template + i;
		const byte*		data;
		ulint			len;
		ulint			field_no;

		field_no = rec_clust
			? templ->clust_rec_field_no : templ->rec_field_no;

		if (UNIV_UNLIKELY(rec_offs_nth_extern(offsets, field_no))) {


			ut_a(!prebuilt->trx->has_search_latch);

			if (UNIV_UNLIKELY(templ->type == DATA_BLOB)) {
				if (prebuilt->blob_heap == NULL) {
					prebuilt->blob_heap = mem_heap_create(
						UNIV_PAGE_SIZE);
				}

				heap = prebuilt->blob_heap;
			} else {
				extern_field_heap
					= mem_heap_create(UNIV_PAGE_SIZE);

				heap = extern_field_heap;
			}


			data = btr_rec_copy_externally_stored_field(
				rec, offsets,
				dict_table_zip_size(prebuilt->table),
				field_no, &len, heap);

			if (UNIV_UNLIKELY(!data)) {


				if (extern_field_heap) {
					mem_heap_free(extern_field_heap);
				}

				return(FALSE);
			}

			ut_a(len != UNIV_SQL_NULL);
		} else {


			data = rec_get_nth_field(rec, offsets, field_no, &len);

			if (UNIV_UNLIKELY(templ->type == DATA_BLOB)
			    && len != UNIV_SQL_NULL) {


				if (prebuilt->blob_heap == NULL) {
					prebuilt->blob_heap = mem_heap_create(
						UNIV_PAGE_SIZE);
				}

				data = memcpy(mem_heap_alloc(
						prebuilt->blob_heap, len),
						data, len);
			}
		}

		if (len != UNIV_SQL_NULL) {
			row_sel_field_store_in_mysql_format(
				mysql_rec + templ->mysql_col_offset,
				templ, data, len);


			if (extern_field_heap) {
				mem_heap_free(extern_field_heap);
				extern_field_heap = NULL;
			}

			if (templ->mysql_null_bit_mask) {


				mysql_rec[templ->mysql_null_byte_offset]
					&= ~(byte) templ->mysql_null_bit_mask;
			}
		} else {


			UNIV_MEM_ASSERT_RW(prebuilt->default_rec
					   + templ->mysql_col_offset,
					   templ->mysql_col_len);
			mysql_rec[templ->mysql_null_byte_offset]
				|= (byte) templ->mysql_null_bit_mask;
			memcpy(mysql_rec + templ->mysql_col_offset,
			       (const byte*) prebuilt->default_rec
			       + templ->mysql_col_offset,
			       templ->mysql_col_len);
		}
	}

	return(TRUE);
}
