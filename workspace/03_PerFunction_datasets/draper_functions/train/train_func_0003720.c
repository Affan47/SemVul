dissolve_free_huge_pages(unsigned long start_pfn, unsigned long end_pfn)
{
	unsigned long pfn;

	if (!hugepages_supported())
		return;

	for (pfn = start_pfn; pfn < end_pfn; pfn += 1 << minimum_order)
		dissolve_free_huge_page(pfn_to_page(pfn));
}
