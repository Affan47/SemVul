print_filemap(void)
{
	filemap_t  *map = filemap;
	file_entry_t *entry;
	int			i;

	for (i = 0; i < map->narray; i++)
	{
		entry = map->array[i];
		if (entry->action != FILE_ACTION_NONE ||
			entry->pagemap.bitmapsize > 0)
		{
			printf("%s (%s)\n", entry->path, action_to_str(entry->action));

			if (entry->pagemap.bitmapsize > 0)
				datapagemap_print(&entry->pagemap);
		}
	}
	fflush(stdout);
}
