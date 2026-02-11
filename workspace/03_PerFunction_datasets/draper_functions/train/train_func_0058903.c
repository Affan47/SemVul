ck_rhs_set_probes(struct ck_rhs_map *map, long offset, unsigned int value)
{

	if (CK_CC_UNLIKELY(map->read_mostly))
		map->entries.no_entries.descs[offset].probes = value;
	else
		map->entries.descs[offset].probes = value;
}
