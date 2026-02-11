row_sel_sec_rec_is_for_blob(

	ulint		mtype,
	ulint		prtype,
	ulint		mbminmaxlen,

	const byte*	clust_field,


	ulint		clust_len,
	const byte*	sec_field,
	ulint		sec_len,
	ulint		prefix_len,

	dict_table_t*	table)
{
	ulint	len;
	byte	buf[REC_VERSION_56_MAX_INDEX_COL_LEN];
	ulint	zip_size = dict_table_flags_to_zip_size(table->flags);


	ut_ad(dict_table_get_format(table) >= DICT_TF_FORMAT_ZIP);
	ut_a(clust_len >= BTR_EXTERN_FIELD_REF_SIZE);
	ut_ad(prefix_len >= sec_len);
	ut_ad(prefix_len > 0);
	ut_a(prefix_len <= sizeof buf);

	if (UNIV_UNLIKELY
	    (!memcmp(clust_field + clust_len - BTR_EXTERN_FIELD_REF_SIZE,
		     field_ref_zero, BTR_EXTERN_FIELD_REF_SIZE))) {


		return(FALSE);
	}

	len = btr_copy_externally_stored_field_prefix(buf, prefix_len,
						      zip_size,
						      clust_field, clust_len);

	if (UNIV_UNLIKELY(len == 0)) {


		return(FALSE);
	}

	len = dtype_get_at_most_n_mbchars(prtype, mbminmaxlen,
					  prefix_len, len, (const char*) buf);

	return(!cmp_data_data(mtype, prtype, buf, len, sec_field, sec_len));
}
