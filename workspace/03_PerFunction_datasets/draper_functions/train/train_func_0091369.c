memory_present(int nid, unsigned long start, unsigned long end)
{
	unsigned long pfn;

	start &= PAGE_SECTION_MASK;
	mminit_validate_memmodel_limits(&start, &end);
	for (pfn = start; pfn < end; pfn += PAGES_PER_SECTION) {
		unsigned long section = pfn_to_section_nr(pfn);
		struct mem_section *ms;

		sparse_index_init(section, nid);
		set_section_nid(section, nid);

		ms = __nr_to_section(section);
		if (!ms->section_mem_map)
			ms->section_mem_map = sparse_encode_early_nid(nid) |
							SECTION_MARKED_PRESENT;
	}
}
