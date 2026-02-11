mdb_sql_listtables(MdbSQL *sql)
{
	unsigned int i;
	MdbCatalogEntry *entry;
	MdbHandle *mdb = sql->mdb;
	MdbField fields[1];
	unsigned char row_buffer[MDB_PGSIZE];
	int row_size;
	MdbTableDef *ttable;
	gchar tmpstr[100];
	int tmpsiz;

	if (!mdb) {
		mdb_sql_error(sql, "You must connect to a database first");
		return;
	}
	mdb_read_catalog (mdb, MDB_TABLE);

	ttable = mdb_create_temp_table(mdb, "#listtables");
	mdb_sql_add_temp_col(sql, ttable, 0, "Tables", MDB_TEXT, 30, 0);


 	for (i=0; i < mdb->num_catalog; i++) {
     		entry = g_ptr_array_index (mdb->catalog, i);
     		if (mdb_is_user_table(entry)) {

			tmpsiz = mdb_ascii2unicode(mdb, entry->object_name, 0, tmpstr, 100);
			mdb_fill_temp_field(&fields[0],tmpstr, tmpsiz, 0,0,0,0);
			row_size = mdb_pack_row(ttable, row_buffer, 1, fields);
			mdb_add_row_to_pg(ttable,row_buffer, row_size);
			ttable->num_rows++;
		}
	}
	sql->cur_table = ttable;

}
