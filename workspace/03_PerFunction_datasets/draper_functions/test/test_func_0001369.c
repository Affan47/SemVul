add_memory_block(int base_section_nr)
{
	struct memory_block *mem;
	int i, ret, section_count = 0, section_nr;

	for (i = base_section_nr;
	     (i < base_section_nr + sections_per_block) && i < NR_MEM_SECTIONS;
	     i++) {
		if (!present_section_nr(i))
			continue;
		if (section_count == 0)
			section_nr = i;
		section_count++;
	}

	if (section_count == 0)
		return 0;
	ret = init_memory_block(&mem, __nr_to_section(section_nr), MEM_ONLINE);
	if (ret)
		return ret;
	mem->section_count = section_count;
	return 0;
}
