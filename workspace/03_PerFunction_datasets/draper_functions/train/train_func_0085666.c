btr_copy_externally_stored_field_prefix(

	byte*		buf,
	ulint		len,
	ulint		zip_size,

	const byte*	data,


	ulint		local_len)
{
	ulint	space_id;
	ulint	page_no;
	ulint	offset;

	ut_a(local_len >= BTR_EXTERN_FIELD_REF_SIZE);

	local_len -= BTR_EXTERN_FIELD_REF_SIZE;

	if (UNIV_UNLIKELY(local_len >= len)) {
		memcpy(buf, data, len);
		return(len);
	}

	memcpy(buf, data, local_len);
	data += local_len;

	ut_a(memcmp(data, field_ref_zero, BTR_EXTERN_FIELD_REF_SIZE));

	if (!mach_read_from_4(data + BTR_EXTERN_LEN + 4)) {


		return(0);
	}

	space_id = mach_read_from_4(data + BTR_EXTERN_SPACE_ID);

	page_no = mach_read_from_4(data + BTR_EXTERN_PAGE_NO);

	offset = mach_read_from_4(data + BTR_EXTERN_OFFSET);

	return(local_len
	       + btr_copy_externally_stored_field_prefix_low(buf + local_len,
							     len - local_len,
							     zip_size,
							     space_id, page_no,
							     offset));
}
