grow_zone_span(struct zone *zone, unsigned long start_pfn,
				     unsigned long end_pfn)
{
	unsigned long old_zone_end_pfn;

	zone_span_writelock(zone);

	old_zone_end_pfn = zone_end_pfn(zone);
	if (zone_is_empty(zone) || start_pfn < zone->zone_start_pfn)
		zone->zone_start_pfn = start_pfn;

	zone->spanned_pages = max(old_zone_end_pfn, end_pfn) -
				zone->zone_start_pfn;

	zone_span_writeunlock(zone);
}
