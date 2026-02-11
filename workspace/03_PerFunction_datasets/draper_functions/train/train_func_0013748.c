add_memory_region (struct e820entry *e820_map,
			       int *e820_nr_map,
			       UINT64 start,
			       UINT64 size,
			       UINT32 type)
{
	int x = *e820_nr_map;

	if (x == E820_MAX) {
		Print(L"Too many entries in the memory map!\n");
		return;
	}

	if ((x > 0) && e820_map[x-1].addr + e820_map[x-1].size == start
	    && e820_map[x-1].type == type)
		e820_map[x-1].size += size;
	else {
		e820_map[x].addr = start;
		e820_map[x].size = size;
		e820_map[x].type = type;
		(*e820_nr_map)++;
	}
}
