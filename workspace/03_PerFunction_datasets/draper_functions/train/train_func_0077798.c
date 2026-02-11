dtuple_convert_back_big_rec(

	dict_index_t*	index __attribute__((unused)),
	dtuple_t*	entry,
	big_rec_t*	vector)

{
	big_rec_field_t*		b	= vector->fields;
	const big_rec_field_t* const	end	= b + vector->n_fields;

	for (; b < end; b++) {
		dfield_t*	dfield;
		ulint		local_len;

		dfield = dtuple_get_nth_field(entry, b->field_no);
		local_len = dfield_get_len(dfield);

		ut_ad(dfield_is_ext(dfield));
		ut_ad(local_len >= BTR_EXTERN_FIELD_REF_SIZE);

		local_len -= BTR_EXTERN_FIELD_REF_SIZE;


		ut_ad(local_len <= DICT_ANTELOPE_MAX_INDEX_COL_LEN);

		dfield_set_data(dfield,
				(char*) b->data - local_len,
				b->len + local_len);
	}

	mem_heap_free(vector->heap);
}
