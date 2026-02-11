memblock_x86_fill(void)
{
	int i;
	u64 end;


	memblock_allow_resize();

	for (i = 0; i < e820.nr_map; i++) {
		struct e820entry *ei = &e820.map[i];

		end = ei->addr + ei->size;
		if (end != (resource_size_t)end)
			continue;

		if (ei->type != E820_RAM && ei->type != E820_RESERVED_KERN)
			continue;

		memblock_add(ei->addr, ei->size);
	}


	memblock_trim_memory(PAGE_SIZE);

	memblock_dump_all();
}
