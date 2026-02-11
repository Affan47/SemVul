page_zip_rec_set_owned(

	page_zip_des_t*	page_zip,
	const byte*	rec,
	ulint		flag)
{
	byte*	slot = page_zip_dir_find(page_zip, page_offset(rec));
	ut_a(slot);
	UNIV_MEM_ASSERT_RW(page_zip->data, page_zip_get_size(page_zip));
	if (flag) {
		*slot |= (PAGE_ZIP_DIR_SLOT_OWNED >> 8);
	} else {
		*slot &= ~(PAGE_ZIP_DIR_SLOT_OWNED >> 8);
	}
}
