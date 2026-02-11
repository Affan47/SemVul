mdb_read_next_dpg(MdbTableDef *table)
{
	MdbCatalogEntry *entry = table->entry;
	MdbHandle *mdb = entry->mdb;
	int next_pg;

#ifndef SLOW_READ
	while (1) {
		next_pg = mdb_map_find_next(mdb, table->usage_map,
			table->map_sz, table->cur_phys_pg);
		if (next_pg < 0)
			break;
		if (!next_pg)
			return 0;

		if (!mdb_read_pg(mdb, next_pg)) {
			fprintf(stderr, "error: reading page %d failed.\n", next_pg);
			return 0;
		}

		table->cur_phys_pg = next_pg;
		if (mdb->pg_buf[0]==MDB_PAGE_DATA && mdb_get_int32(mdb->pg_buf, 4)==entry->table_pg)
			return table->cur_phys_pg;


		fprintf(stderr,
			"warning: page %d from map doesn't match: Type=%d, buf[4..7]=%ld Expected table_pg=%ld\n",
			next_pg, mdb->pg_buf[0], mdb_get_int32(mdb->pg_buf, 4), entry->table_pg);
	}
	fprintf(stderr, "Warning: defaulting to brute force read\n");
#endif

	do {
		if (!mdb_read_pg(mdb, table->cur_phys_pg++))
			return 0;
	} while (mdb->pg_buf[0]!=MDB_PAGE_DATA || mdb_get_int32(mdb->pg_buf, 4)!=entry->table_pg);

	return table->cur_phys_pg;
}
