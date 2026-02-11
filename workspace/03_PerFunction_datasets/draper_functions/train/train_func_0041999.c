zalloc_dump_zones_log(logagent_t *la)
{
	struct zonesize_filler filler;
	size_t i, zpages, blocks, subzones;
	size_t bytes, wasted, overhead;

	if (NULL == zt)
		return;

	zalloc_sort_zones(&filler);

	zpages = blocks = subzones = 0;
	bytes = wasted = overhead = 0;

	for (i = 0; i < filler.count; i++) {
		zone_t *zone = filler.array[i].zone;
		unsigned bcnt, over;
		size_t remain;
		char buf[16];

		bcnt = zone->zn_blocks - zone->zn_cnt;
		g_assert(uint_is_non_negative(bcnt));

		blocks += bcnt;
		bytes += size_saturate_mult(bcnt, zone->zn_size);
		remain = zone->zn_arena.sz_size % zone->zn_size;
		wasted += size_saturate_mult(zone->zn_subzones, remain);
		subzones += zone->zn_subzones;
		zpages += vmm_page_count(zone->zn_arena.sz_size) * zone->zn_subzones;

		over = sizeof(*zone) + (zone->zn_subzones - 1) * sizeof(zone->zn_arena);
		if (zone->zn_gc != NULL) {
			struct zone_gc *zg = zone->zn_gc;
			over += sizeof(*zg);
			over += zg->zg_zones * sizeof(zg->zg_subzinfo[0]);
		}
		overhead += over;

		if (zone->private) {
			str_bprintf(buf, sizeof buf, ", stid=%u", zone->zn_stid);
		} else {
			buf[0] = 0;
		}

		log_info(la, "ZALLOC zone(%zu bytes%s): "
			"blocks=%u, free=%u, %u %zuK-subzone%s, over=%u, %s mode",
			zone->zn_size, buf, zone->zn_blocks, bcnt, zone->zn_subzones,
			zone->zn_arena.sz_size / 1024,
			1 == zone->zn_subzones ? "" : "s", over,
			zone->zn_gc != NULL ? "GC" : "normal");
	}

	overhead += hash_table_memory(zt);

	log_info(la, "ZALLOC zones have %zu bytes (%s) free among %zu block%s",
		bytes, short_size(bytes, FALSE), blocks, 1 == blocks ? "" : "s");

	log_info(la, "ZALLOC zones wasting %zu bytes (%s) among %zu subzone%s "
		"(%zu page%s)",
		wasted, short_size(wasted, FALSE),
		subzones, 1 == subzones ? "" : "s", zpages, 1 == zpages ? "" : "s");

	log_info(la, "ZALLOC zones structural overhead totals %zu bytes (%s)",
		overhead, short_size(overhead, FALSE));

	xfree(filler.array);
}
