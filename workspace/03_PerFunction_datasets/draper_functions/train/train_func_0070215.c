fil_read_first_page(

	os_file_t	data_file,
	ibool		one_read_already,


	ulint*		flags,
#ifdef UNIV_LOG_ARCHIVE
	ulint*		min_arch_log_no,

	ulint*		max_arch_log_no,

#endif
	ib_uint64_t*	min_flushed_lsn,

	ib_uint64_t*	max_flushed_lsn)

{
	byte*		buf;
	page_t*		page;
	ib_uint64_t	flushed_lsn;
	const char*	check_msg = NULL;

	buf = ut_malloc(2 * UNIV_PAGE_SIZE);

	page = ut_align(buf, UNIV_PAGE_SIZE);

	os_file_read(data_file, page, 0, 0, UNIV_PAGE_SIZE);

	*flags = mach_read_from_4(FSP_HEADER_OFFSET + FSP_SPACE_FLAGS + page);

	flushed_lsn = mach_read_from_8(page + FIL_PAGE_FILE_FLUSH_LSN);

	if (!one_read_already) {
		check_msg = fil_check_first_page(page);
	}

	ut_free(buf);

	if (check_msg) {
		return(check_msg);
	}

	if (!one_read_already) {
		*min_flushed_lsn = flushed_lsn;
		*max_flushed_lsn = flushed_lsn;
#ifdef UNIV_LOG_ARCHIVE
		*min_arch_log_no = arch_log_no;
		*max_arch_log_no = arch_log_no;
#endif
		return(NULL);
	}

	if (*min_flushed_lsn > flushed_lsn) {
		*min_flushed_lsn = flushed_lsn;
	}
	if (*max_flushed_lsn < flushed_lsn) {
		*max_flushed_lsn = flushed_lsn;
	}
#ifdef UNIV_LOG_ARCHIVE
	if (*min_arch_log_no > arch_log_no) {
		*min_arch_log_no = arch_log_no;
	}
	if (*max_arch_log_no < arch_log_no) {
		*max_arch_log_no = arch_log_no;
	}
#endif

	return(NULL);
}
