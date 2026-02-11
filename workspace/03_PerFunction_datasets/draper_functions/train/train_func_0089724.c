mdb_map_find_next_freepage(MdbTableDef *table, int row_size)
{
	MdbCatalogEntry *entry = table->entry;
	MdbHandle *mdb = entry->mdb;
	guint32 pgnum;
	guint32 cur_pg = 0;
	int free_space;

	do {
		pgnum = mdb_map_find_next(mdb,
				table->free_usage_map,
				table->freemap_sz, cur_pg);

		if (!pgnum) {

			pgnum = mdb_alloc_page(table);
			return pgnum;
		} else if (pgnum==-1) {
			fprintf(stderr, "Error: mdb_map_find_next_freepage error while reading maps.\n");
			exit(1);
		}
		cur_pg = pgnum;

		mdb_read_pg(mdb, pgnum);
		free_space = mdb_pg_get_freespace(mdb);

	} while (free_space < row_size);


	return pgnum;
}
