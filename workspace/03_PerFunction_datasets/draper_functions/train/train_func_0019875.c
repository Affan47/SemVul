xen_foreach_remap_area(unsigned long nr_pages,
	unsigned long (*func)(unsigned long start_pfn, unsigned long end_pfn,
			      unsigned long nr_pages, unsigned long last_val))
{
	phys_addr_t start = 0;
	unsigned long ret_val = 0;
	const struct e820entry *entry = xen_e820_map;
	int i;


	for (i = 0; i < xen_e820_map_entries; i++, entry++) {
		phys_addr_t end = entry->addr + entry->size;
		if (entry->type == E820_RAM || i == xen_e820_map_entries - 1) {
			unsigned long start_pfn = PFN_DOWN(start);
			unsigned long end_pfn = PFN_UP(end);

			if (entry->type == E820_RAM)
				end_pfn = PFN_UP(entry->addr);

			if (start_pfn < end_pfn)
				ret_val = func(start_pfn, end_pfn, nr_pages,
					       ret_val);
			start = end;
		}
	}

	return ret_val;
}
