ck_rhs_entry(struct ck_rhs_map *map, long offset)
{

	if (map->read_mostly)
		return (map->entries.no_entries.entries[offset]);
	else
		return (map->entries.descs[offset].entry);
}
