btr_node_ptr_set_child_page_no(

	rec_t*		rec,
	page_zip_des_t*	page_zip,

	const ulint*	offsets,
	ulint		page_no,
	mtr_t*		mtr)
{
	byte*	field;
	ulint	len;

	ut_ad(rec_offs_validate(rec, NULL, offsets));
	ut_ad(!page_is_leaf(page_align(rec)));
	ut_ad(!rec_offs_comp(offsets) || rec_get_node_ptr_flag(rec));


	field = rec_get_nth_field(rec, offsets,
				  rec_offs_n_fields(offsets) - 1, &len);

	ut_ad(len == REC_NODE_PTR_SIZE);

	if (UNIV_LIKELY_NULL(page_zip)) {
		page_zip_write_node_ptr(page_zip, rec,
					rec_offs_data_size(offsets),
					page_no, mtr);
	} else {
		mlog_write_ulint(field, page_no, MLOG_4BYTES, mtr);
	}
}
