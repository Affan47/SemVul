e820_mark_nosave_regions(unsigned long limit_pfn)
{
	int i;
	unsigned long pfn = 0;

	for (i = 0; i < e820.nr_map; i++) {
		struct e820entry *ei = &e820.map[i];

		if (pfn < PFN_UP(ei->addr))
			register_nosave_region(pfn, PFN_UP(ei->addr));

		pfn = PFN_DOWN(ei->addr + ei->size);

		if (ei->type != E820_RAM && ei->type != E820_RESERVED_KERN)
			register_nosave_region(PFN_UP(ei->addr), pfn);

		if (pfn >= limit_pfn)
			break;
	}
}
