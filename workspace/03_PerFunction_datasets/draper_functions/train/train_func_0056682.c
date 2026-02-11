GetFatMap(Fs_t *Stream)
{
	int nr_entries,i;
	FatMap_t *map;

	Stream->fat_error = 0;
	nr_entries = (Stream->fat_len + SECT_PER_ENTRY - 1) / SECT_PER_ENTRY;
	map = NewArray(nr_entries, FatMap_t);
	if(!map)
		return 0;

	for(i=0; i< nr_entries; i++) {
		map[i].data = 0;
		map[i].valid = 0;
		map[i].dirty = 0;
	}

	return map;
}
