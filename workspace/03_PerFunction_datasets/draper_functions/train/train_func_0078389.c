mdb_update_index(MdbTableDef *table, MdbIndex *idx, unsigned int num_fields, MdbField *fields, guint32 pgnum, guint16 rownum)
{
	MdbCatalogEntry *entry = table->entry;
	MdbHandle *mdb = entry->mdb;
	int idx_xref[16];
	unsigned int i, j;
	MdbIndexChain *chain;
	MdbField idx_fields[10];

	for (i = 0; i < idx->num_keys; i++) {
		for (j = 0; j < num_fields; j++) {

			if (fields[j].colnum == idx->key_col_num[i]-1) {
				idx_xref[i] = j;
				idx_fields[i] = fields[j];
			}
		}
	}


	chain = g_malloc0(sizeof(MdbIndexChain));

	mdb_index_find_row(mdb, idx, chain, pgnum, rownum);


	mdb_add_row_to_leaf_pg(table, idx, &chain->pages[chain->cur_depth-1], idx_fields, pgnum, rownum);

	return 1;
}
