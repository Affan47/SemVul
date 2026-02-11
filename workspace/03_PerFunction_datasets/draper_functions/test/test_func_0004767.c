__register_nosave_region(unsigned long start_pfn, unsigned long end_pfn,
			 int use_kmalloc)
{
	struct nosave_region *region;

	if (start_pfn >= end_pfn)
		return;

	if (!list_empty(&nosave_regions)) {

		region = list_entry(nosave_regions.prev,
					struct nosave_region, list);
		if (region->end_pfn == start_pfn) {
			region->end_pfn = end_pfn;
			goto Report;
		}
	}
	if (use_kmalloc) {

		region = kmalloc(sizeof(struct nosave_region), GFP_KERNEL);
		BUG_ON(!region);
	} else

		region = memblock_virt_alloc(sizeof(struct nosave_region), 0);
	region->start_pfn = start_pfn;
	region->end_pfn = end_pfn;
	list_add_tail(&region->list, &nosave_regions);
 Report:
	printk(KERN_INFO "PM: Registered nosave memory: [mem %#010llx-%#010llx]\n",
		(unsigned long long) start_pfn << PAGE_SHIFT,
		((unsigned long long) end_pfn << PAGE_SHIFT) - 1);
}
