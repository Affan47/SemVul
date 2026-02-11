bin_info_run_size_calc(arena_bin_info_t *bin_info, size_t min_run_size)
{
	size_t try_run_size, good_run_size;
	uint32_t try_nregs, good_nregs;
	uint32_t try_hdr_size, good_hdr_size;
	uint32_t try_bitmap_offset, good_bitmap_offset;
#ifdef JEMALLOC_PROF
	uint32_t try_ctx0_offset, good_ctx0_offset;
#endif
	uint32_t try_reg0_offset, good_reg0_offset;

	assert(min_run_size >= PAGE_SIZE);
	assert(min_run_size <= arena_maxclass);


	try_run_size = min_run_size;
	try_nregs = ((try_run_size - sizeof(arena_run_t)) / bin_info->reg_size)
	    + 1;
	if (try_nregs > RUN_MAXREGS) {
		try_nregs = RUN_MAXREGS
		    + 1;
	}
	do {
		try_nregs--;
		try_hdr_size = sizeof(arena_run_t);

		try_hdr_size = LONG_CEILING(try_hdr_size);
		try_bitmap_offset = try_hdr_size;

		try_hdr_size += bitmap_size(try_nregs);
#ifdef JEMALLOC_PROF
		if (opt_prof && prof_promote == false) {

			try_hdr_size = QUANTUM_CEILING(try_hdr_size);
			try_ctx0_offset = try_hdr_size;

			try_hdr_size += try_nregs * sizeof(prof_ctx_t *);
		} else
			try_ctx0_offset = 0;
#endif
		try_reg0_offset = try_run_size - (try_nregs *
		    bin_info->reg_size);
	} while (try_hdr_size > try_reg0_offset);


	do {


		good_run_size = try_run_size;
		good_nregs = try_nregs;
		good_hdr_size = try_hdr_size;
		good_bitmap_offset = try_bitmap_offset;
#ifdef JEMALLOC_PROF
		good_ctx0_offset = try_ctx0_offset;
#endif
		good_reg0_offset = try_reg0_offset;


		try_run_size += PAGE_SIZE;
		try_nregs = ((try_run_size - sizeof(arena_run_t)) /
		    bin_info->reg_size)
		    + 1;
		if (try_nregs > RUN_MAXREGS) {
			try_nregs = RUN_MAXREGS
			    + 1;
		}
		do {
			try_nregs--;
			try_hdr_size = sizeof(arena_run_t);

			try_hdr_size = LONG_CEILING(try_hdr_size);
			try_bitmap_offset = try_hdr_size;

			try_hdr_size += bitmap_size(try_nregs);
#ifdef JEMALLOC_PROF
			if (opt_prof && prof_promote == false) {

				try_hdr_size = QUANTUM_CEILING(try_hdr_size);
				try_ctx0_offset = try_hdr_size;


				try_hdr_size += try_nregs *
				    sizeof(prof_ctx_t *);
			}
#endif
			try_reg0_offset = try_run_size - (try_nregs *
			    bin_info->reg_size);
		} while (try_hdr_size > try_reg0_offset);
	} while (try_run_size <= arena_maxclass
	    && try_run_size <= arena_maxclass
	    && RUN_MAX_OVRHD * (bin_info->reg_size << 3) > RUN_MAX_OVRHD_RELAX
	    && (try_reg0_offset << RUN_BFP) > RUN_MAX_OVRHD * try_run_size
	    && try_nregs < RUN_MAXREGS);

	assert(good_hdr_size <= good_reg0_offset);


	bin_info->run_size = good_run_size;
	bin_info->nregs = good_nregs;
	bin_info->bitmap_offset = good_bitmap_offset;
#ifdef JEMALLOC_PROF
	bin_info->ctx0_offset = good_ctx0_offset;
#endif
	bin_info->reg0_offset = good_reg0_offset;

	return (good_run_size);
}
