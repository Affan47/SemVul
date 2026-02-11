read_sadump(int fd, void *bufptr, int cnt, ulong addr, physaddr_t paddr)
{
	physaddr_t curpaddr ATTRIBUTE_UNUSED;
	uint64_t pfn, whole_offset, perdisk_offset, block;
	ulong page_offset;
	int dfd;

	if (sd->flags & SADUMP_KDUMP_BACKUP &&
	    paddr >= sd->backup_src_start &&
	    paddr < sd->backup_src_start + sd->backup_src_size) {
		ulong orig_paddr;

		orig_paddr = paddr;
		paddr += sd->backup_offset - sd->backup_src_start;

		if (CRASHDEBUG(1))
			error(INFO, "sadump: kdump backup region: %#llx => %#llx\n",
			      orig_paddr, paddr);

	}

	pfn = paddr_to_pfn(paddr);

	curpaddr = paddr & ~((physaddr_t)(sd->block_size-1));
	page_offset = paddr & ((physaddr_t)(sd->block_size-1));

	if ((pfn >= sd->dump_header->max_mapnr) || !page_is_ram(pfn))
		return SEEK_ERROR;
	if (!page_is_dumpable(pfn)) {
		if (sd->flags & SADUMP_ZERO_EXCLUDED)
			return PAGE_EXCLUDED;
		memset(bufptr, 0, cnt);
		return cnt;
	}

	block = pfn_to_block(pfn);

	whole_offset = block * sd->block_size;

	if (sd->flags & SADUMP_DISKSET) {
		int diskid;

		if (!lookup_diskset(whole_offset, &diskid, &perdisk_offset))
			return SEEK_ERROR;

		dfd = sd->sd_list[diskid]->dfd;
		perdisk_offset += sd->sd_list[diskid]->data_offset;

	} else {
		dfd = sd->dfd;
		perdisk_offset = whole_offset + sd->data_offset;

	}

	if (lseek(dfd, perdisk_offset, SEEK_SET) == failed)
		return SEEK_ERROR;

	if (read(dfd, sd->page_buf, sd->block_size) != sd->block_size)
		return READ_ERROR;

	memcpy(bufptr, sd->page_buf + page_offset, cnt);

	return cnt;
}
