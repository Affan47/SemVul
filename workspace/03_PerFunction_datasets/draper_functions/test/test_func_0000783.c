mdb_sql_select(MdbSQL *sql)
{
unsigned int i,j;
MdbHandle *mdb = sql->mdb;
MdbTableDef *table = NULL;
MdbSQLTable *sql_tab;
MdbColumn *col;
MdbSQLColumn *sqlcol;
int found = 0;

	if (!mdb) {
		mdb_sql_error(sql, "You must connect to a database first");
		return;
	}

	sql_tab = g_ptr_array_index(sql->tables,0);

	table = mdb_read_table_by_name(mdb, sql_tab->name, MDB_TABLE);
	if (!table) {
		mdb_sql_error(sql, "%s is not a table in this database", sql_tab->name);

		mdb_sql_reset(sql);
		return;
	}
	mdb_read_columns(table);
	mdb_read_indices(table);
	mdb_rewind_table(table);

	if (sql->all_columns) {
		for (i=0;i<table->num_cols;i++) {
			col = g_ptr_array_index(table->columns,i);
			mdb_sql_add_column(sql, col->name);
		}
	}

	for (i=0;i<sql->num_columns;i++) {
		sqlcol = g_ptr_array_index(sql->columns,i);
		found=0;
		for (j=0;j<table->num_cols;j++) {
			col=g_ptr_array_index(table->columns,j);
			if (!strcasecmp(sqlcol->name, col->name)) {
				sqlcol->disp_size = mdb_col_disp_size(col);
				found=1;
				break;
			}
		}
		if (!found) {
			mdb_sql_error(sql, "Column %s not found",sqlcol->name);
			mdb_sql_reset(sql);
			return;
		}
	}


	if (sql->sarg_tree) {
		mdb_sql_walk_tree(sql->sarg_tree, mdb_sql_find_sargcol, table);
		mdb_sql_walk_tree(sql->sarg_tree, mdb_find_indexable_sargs, NULL);
	}


	table->sarg_tree = sql->sarg_tree;
	sql->sarg_tree = NULL;

	sql->cur_table = table;
	mdb_index_scan_init(mdb, table);
}
