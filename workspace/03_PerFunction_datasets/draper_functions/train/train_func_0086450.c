zalloc(zone_t *zone)
{
	char **blk;


	zlock(zone);

	zstats.allocations++;
	zstats.user_blocks++;
	zstats.user_memory += zone->zn_size;
	memusage_add_one(zone->zn_mem);


	blk = zone->zn_free;
	if G_LIKELY(blk != NULL) {
		zone->zn_free = (char **) *blk;
		zone->zn_cnt++;
		safety_assert(zone->zn_free != NULL || zone->zn_blocks == zone->zn_cnt);
		safety_assert(NULL == zone->zn_free || zbelongs(zone, zone->zn_free));
		zunlock(zone);
		return zprepare(zone, blk);
	}


	if G_UNLIKELY(zone->zn_gc != NULL)
		return zgc_zalloc(zone);


	g_assert(zone->zn_blocks == zone->zn_cnt);


	blk = zn_extend(zone);
	zone->zn_free = (char **) *blk;
	zone->zn_cnt++;
	safety_assert(NULL == zone->zn_free || zbelongs(zone, zone->zn_free));

	zunlock(zone);
	return zprepare(zone, blk);
}
