add_memmap(struct memory_range *memmap_p, unsigned long long addr,
								size_t size)
{
	int i, j, nr_entries = 0, tidx = 0, align = 1024;
	unsigned long long mstart, mend;


	if ((addr%align) || (size%align))
		return -1;


	for (i = 0; i < CRASH_MAX_MEMMAP_NR;  i++) {
		mstart = memmap_p[i].start;
		mend = memmap_p[i].end;
		if (!mstart  && !mend)
			break;
		else
			nr_entries++;
	}
	if (nr_entries == CRASH_MAX_MEMMAP_NR)
		return -1;

	for (i = 0; i < CRASH_MAX_MEMMAP_NR;  i++) {
		mstart = memmap_p[i].start;
		mend = memmap_p[i].end;
		if (mstart == 0 && mend == 0)
			break;
		if (mstart <= (addr+size-1) && mend >=addr)

			return -1;
		else if (addr > mend)
			tidx = i+1;
	}

		for (j = nr_entries-1; j >= tidx; j--)
			memmap_p[j+1] = memmap_p[j];
		memmap_p[tidx].start = addr;
		memmap_p[tidx].end = addr + size - 1;

	dbgprintf("Memmap after adding segment\n");
	for (i = 0; i < CRASH_MAX_MEMMAP_NR;  i++) {
		mstart = memmap_p[i].start;
		mend = memmap_p[i].end;
		if (mstart == 0 && mend == 0)
			break;
		dbgprintf("%016llx - %016llx\n",
			mstart, mend);
	}

	return 0;
}
