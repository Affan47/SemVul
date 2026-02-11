xc_core_elf_pfn_valid(ulong pfn)
{
        int i, b, start_index;
	off_t offset;
	size_t size;
	uint nr_pages;
        ulong tmp;
        uint64_t pfn_batch[MAX_BATCH_SIZE];

        offset = xd->xc_core.header.xch_index_offset;
	nr_pages = xd->xc_core.header.xch_nr_pages;


	xd->xc_core.last_batch.accesses++;
	start_index = 0;

	if ((pfn >= xd->xc_core.last_batch.start) &&
	    (pfn <= xd->xc_core.last_batch.end)) {
		xd->xc_core.last_batch.duplicates++;
		start_index = xd->xc_core.last_batch.index;
	} else {
		for (i = 0; i <= INDEX_PFN_COUNT; i++) {
			if ((i == INDEX_PFN_COUNT) ||
			    (pfn < xd->xc_core.elf_index_pfn[i].pfn)) {
				if (--i < 0)
					i = 0;
				start_index = xd->xc_core.elf_index_pfn[i].index;
				break;
			}
		}
	}

	offset += (start_index * sizeof(uint64_t));
        if (lseek(xd->xfd, offset, SEEK_SET) == -1)
                error(FATAL, "cannot lseek to page index\n");

        for (b = start_index; b < nr_pages; b += MAX_BATCH_SIZE) {
		size = sizeof(uint64_t) * MIN(MAX_BATCH_SIZE, nr_pages - b);
                if (read(xd->xfd, &pfn_batch[0], size) != size) {
                        error(INFO, "cannot read index page %d\n", b);
			return PFN_NOT_FOUND;
		}

		for (i = 0; i < MAX_BATCH_SIZE; i++) {
			if ((b+i) >= nr_pages)
				break;

			tmp = (ulong)pfn_batch[i];

                	if (tmp == pfn) {
				if (CRASHDEBUG(4))
                        		fprintf(xd->ofp,
				            "index: batch: %d found pfn %ld (0x%lx) at index %d\n",
                                		b/MAX_BATCH_SIZE, pfn, pfn, i+b);

				if ((b+MAX_BATCH_SIZE) < nr_pages) {
					xd->xc_core.last_batch.index = b;
					xd->xc_core.last_batch.start = (ulong)pfn_batch[0];
					xd->xc_core.last_batch.end = (ulong)pfn_batch[MAX_BATCH_SIZE-1];
				}

                        	return (i+b);
                	}
		}
        }

        return PFN_NOT_FOUND;
}
