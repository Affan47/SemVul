read_hunk_map(struct chd_file *chd)
{
	UINT32 entrysize = (chd->header.version < 3) ? OLD_MAP_ENTRY_SIZE : MAP_ENTRY_SIZE;
	UINT8 raw_map_entries[MAP_STACK_ENTRIES * MAP_ENTRY_SIZE];
	UINT8 cookie[MAP_ENTRY_SIZE];
	UINT64 fileoffset;
	UINT32 count;
	int i, err;


	chd->map = malloc(sizeof(chd->map[0]) * chd->header.totalhunks);
	if (!chd->map)
		return CHDERR_OUT_OF_MEMORY;


	fileoffset = chd->header.length;
	for (i = 0; i < chd->header.totalhunks; i += MAP_STACK_ENTRIES)
	{

		int entries = chd->header.totalhunks - i, j;
		if (entries > MAP_STACK_ENTRIES)
			entries = MAP_STACK_ENTRIES;


		count = multi_read(chd->file, fileoffset, entries * entrysize, raw_map_entries);
		if (count != entries * entrysize)
		{
			err = CHDERR_READ_ERROR;
			goto cleanup;
		}
		fileoffset += entries * entrysize;


		if (entrysize == MAP_ENTRY_SIZE)
		{
			for (j = 0; j < entries; j++)
				extract_map_entry(&raw_map_entries[j * MAP_ENTRY_SIZE], &chd->map[i + j]);
		}
		else
		{
			for (j = 0; j < entries; j++)
				extract_old_map_entry(&raw_map_entries[j * OLD_MAP_ENTRY_SIZE], &chd->map[i + j], chd->header.hunkbytes);
		}
	}


	count = multi_read(chd->file, fileoffset, entrysize, &cookie);
	if (count != entrysize || memcmp(&cookie, END_OF_LIST_COOKIE, entrysize))
	{
		err = CHDERR_INVALID_FILE;
		goto cleanup;
	}
	return CHDERR_NONE;

cleanup:
	if (chd->map)
		free(chd->map);
	chd->map = NULL;
	return err;
}
