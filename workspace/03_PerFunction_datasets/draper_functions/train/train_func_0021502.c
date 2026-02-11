show_valid_zones(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct memory_block *mem = to_memory_block(dev);
	unsigned long start_pfn, end_pfn;
	unsigned long valid_start, valid_end;
	unsigned long nr_pages = PAGES_PER_SECTION * sections_per_block;
	struct zone *zone;

	start_pfn = section_nr_to_pfn(mem->start_section_nr);
	end_pfn = start_pfn + nr_pages;


	if (!test_pages_in_a_zone(start_pfn, end_pfn, &valid_start, &valid_end))
		return sprintf(buf, "none\n");

	zone = page_zone(pfn_to_page(valid_start));

	if (zone_idx(zone) == ZONE_MOVABLE - 1) {

		if (valid_end == zone_end_pfn(zone))
			return sprintf(buf, "%s %s\n",
					zone->name, (zone + 1)->name);
	}

	if (zone_idx(zone) == ZONE_MOVABLE) {

		if (valid_start == zone->zone_start_pfn)
			return sprintf(buf, "%s %s\n",
					zone->name, (zone - 1)->name);
	}

	return sprintf(buf, "%s\n", zone->name);
}
