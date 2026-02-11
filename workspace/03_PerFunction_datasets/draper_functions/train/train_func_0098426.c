trx_undo_page_fetch_ext(

	byte*		ext_buf,

	ulint		prefix_len,

	ulint		zip_size,

	const byte*	field,
	ulint*		len)

{

	ulint	ext_len = btr_copy_externally_stored_field_prefix(
		ext_buf, prefix_len, zip_size, field, *len);

	ut_a(ext_len);

	memcpy(ext_buf + ext_len,
	       field + *len - BTR_EXTERN_FIELD_REF_SIZE,
	       BTR_EXTERN_FIELD_REF_SIZE);
	*len = ext_len + BTR_EXTERN_FIELD_REF_SIZE;
	return(ext_buf);
}
