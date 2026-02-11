ck_rhs_probes(struct ck_rhs_map *map, long offset)
{

	if (CK_CC_UNLIKELY(map->read_mostly))
		return (map->entries.no_entries.descs[offset].probes);
	else
		return (map->entries.descs[offset].probes);
}
