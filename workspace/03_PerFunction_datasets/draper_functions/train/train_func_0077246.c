insert_record(int line, struct hashmap *map, int pass)
{
	xrecord_t **records = pass == 1 ?
		map->env->xdf1.recs : map->env->xdf2.recs;
	xrecord_t *record = records[line - 1], *other;


	int index = (int)((record->ha << 1) % map->alloc);

	while (map->entries[index].line1) {
		other = map->env->xdf1.recs[map->entries[index].line1 - 1];
		if (map->entries[index].hash != record->ha ||
				!xdl_recmatch(record->ptr, record->size,
					other->ptr, other->size,
					map->xpp->flags)) {
			if (++index >= map->alloc)
				index = 0;
			continue;
		}
		if (pass == 2)
			map->has_matches = 1;
		if (pass == 1 || map->entries[index].line2)
			map->entries[index].line2 = NON_UNIQUE;
		else
			map->entries[index].line2 = line;
		return;
	}
	if (pass == 2)
		return;
	map->entries[index].line1 = line;
	map->entries[index].hash = record->ha;
	if (!map->first)
		map->first = map->entries + index;
	if (map->last) {
		map->last->next = map->entries + index;
		map->entries[index].previous = map->last;
	}
	map->last = map->entries + index;
	map->nr++;
}
