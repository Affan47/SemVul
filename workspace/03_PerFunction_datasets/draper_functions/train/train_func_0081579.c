sparse_mem_maps_populate_node(struct page **map_map,
					  unsigned long pnum_begin,
					  unsigned long pnum_end,
					  unsigned long map_count, int nodeid)
{
	unsigned long pnum;
	unsigned long size = sizeof(struct page) * PAGES_PER_SECTION;
	void *vmemmap_buf_start;

	size = ALIGN(size, PMD_SIZE);
	vmemmap_buf_start = __earlyonly_bootmem_alloc(nodeid, size * map_count,
			 PMD_SIZE, __pa(MAX_DMA_ADDRESS));

	if (vmemmap_buf_start) {
		vmemmap_buf = vmemmap_buf_start;
		vmemmap_buf_end = vmemmap_buf_start + size * map_count;
	}

	for (pnum = pnum_begin; pnum < pnum_end; pnum++) {
		struct mem_section *ms;

		if (!present_section_nr(pnum))
			continue;

		map_map[pnum] = sparse_mem_map_populate(pnum, nodeid);
		if (map_map[pnum])
			continue;
		ms = __nr_to_section(pnum);
		printk(KERN_ERR "%s: sparsemem memory map backing failed "
			"some memory will not be available.\n", __func__);
		ms->section_mem_map = 0;
	}

	if (vmemmap_buf_start) {

		memblock_free_early(__pa(vmemmap_buf),
				    vmemmap_buf_end - vmemmap_buf);
		vmemmap_buf = NULL;
		vmemmap_buf_end = NULL;
	}
}
