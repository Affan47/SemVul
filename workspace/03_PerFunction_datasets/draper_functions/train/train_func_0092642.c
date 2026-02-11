trx_rseg_create(void)

{
	mtr_t		mtr;
	ulint		slot_no;
	trx_rseg_t*	rseg = NULL;

	mtr_start(&mtr);


	mtr_x_lock(fil_space_get_latch(TRX_SYS_SPACE, NULL), &mtr);

	mutex_enter(&kernel_mutex);

	slot_no = trx_sysf_rseg_find_free(&mtr);

	if (slot_no != ULINT_UNDEFINED) {
		ulint		space;
		ulint		page_no;
		ulint		zip_size;
		trx_sysf_t*	sys_header;

		page_no = trx_rseg_header_create(
			TRX_SYS_SPACE, 0, ULINT_MAX, slot_no, &mtr);

		ut_a(page_no != FIL_NULL);

		ut_ad(!trx_rseg_get_on_id(slot_no));

		sys_header = trx_sysf_get(&mtr);

		space = trx_sysf_rseg_get_space(sys_header, slot_no, &mtr);

		zip_size = space ? fil_space_get_zip_size(space) : 0;

		rseg = trx_rseg_mem_create(
			slot_no, space, zip_size, page_no,
			purge_sys->ib_bh, &mtr);
	}

	mutex_exit(&kernel_mutex);
	mtr_commit(&mtr);

	return(rseg);
}
