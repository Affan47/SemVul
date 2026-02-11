lkcd_lseek(physaddr_t paddr)
{
        long i = 0;
	int err;
        int eof;
        void *dp;
        long page = 0;
	physaddr_t physaddr;
	int seeked_to_page = 0;
	off_t page_offset;

	dp = lkcd->dump_page;

	lkcd->curpos = paddr & ((physaddr_t)(lkcd->page_size-1));
        lkcd->curpaddr = paddr & ~((physaddr_t)(lkcd->page_size-1));

	if (page_is_cached())
		return TRUE;


	if(page_is_hashed(&page)) {
		seeked_to_page = 1;
	}


    if ((page_offset = get_offset(paddr)) > 0) {
	off_t seek_offset;
	seek_offset = lseek(lkcd->fd, page_offset, SEEK_SET);

	if (seek_offset == page_offset) {
	    seeked_to_page = 1;
	    page = 0;
	}
    }


    if (seeked_to_page) {
	err = lkcd_load_dump_page_header(dp, page);
	if (err == LKCD_DUMPFILE_OK) {
	    return(cache_page());
	}
    }


    lseek(lkcd->fd, lkcd->page_offset_max, SEEK_SET);
    eof = FALSE;
    while (!eof) {
	if( (i++%2048) == 0) {
	    lkcd_speedo();
	}

	switch (lkcd_load_dump_page_header(dp, page))
	{
	    case LKCD_DUMPFILE_OK:
		break;

	    case LKCD_DUMPFILE_EOF:
		eof = TRUE;
		continue;
	}

	physaddr = lkcd->get_dp_flags() &
	    (LKCD_DUMP_MCLX_V0|LKCD_DUMP_MCLX_V1) ?
	    (lkcd->get_dp_address() - lkcd->kvbase) << lkcd->page_shift:
	    lkcd->get_dp_address() - lkcd->kvbase;

	if (physaddr == lkcd->curpaddr) {
	    return(cache_page());
	}
	lseek(lkcd->fd, lkcd->get_dp_size(), SEEK_CUR);
    }

	return FALSE;
}
