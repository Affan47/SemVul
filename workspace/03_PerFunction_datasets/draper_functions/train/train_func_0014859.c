zgc_insert_freelist(zone_t *zone, char **blk)
{
	struct zone_gc *zg = zone->zn_gc;
	struct subzinfo *szi;
	unsigned idx;

	G_PREFETCH_W(blk);
	G_PREFETCH_W(&zg->zg_free);

	szi = zgc_find_subzone(zg, blk, NULL);

	G_PREFETCH_W(&szi->szi_free_cnt);

	g_assert(szi != NULL);
	g_assert(zgc_within_subzone(szi, blk));


	g_assert(NULL == szi->szi_free || zgc_within_subzone(szi, szi->szi_free));

	*blk = (char *) szi->szi_free;
	szi->szi_free = blk;


	idx = szi - zg->zg_subzinfo;

	g_assert(uint_is_non_negative(idx) && idx < zg->zg_zones);


	if (addr_grows_upwards) {
		if (idx < zg->zg_free)
			zg->zg_free = idx;
	} else {
		if (idx > zg->zg_free)
			zg->zg_free = idx;
	}

	if (++szi->szi_free_cnt == zone->zn_hint)
		return !zgc_subzone_free(zone, szi);

	return TRUE;
}
