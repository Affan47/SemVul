compaction_suitable(struct zone *zone, int order,
					unsigned int alloc_flags,
					int classzone_idx)
{
	enum compact_result ret;

	ret = __compaction_suitable(zone, order, alloc_flags, classzone_idx,
				    zone_page_state(zone, NR_FREE_PAGES));
	trace_mm_compaction_suitable(zone, order, ret);
	if (ret == COMPACT_NOT_SUITABLE_ZONE)
		ret = COMPACT_SKIPPED;

	return ret;
}
