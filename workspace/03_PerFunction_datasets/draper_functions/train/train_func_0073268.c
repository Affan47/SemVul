mdb_sql_bind_all(MdbSQL *sql)
{
	unsigned int i;

	for (i=0;i<sql->num_columns;i++) {
		sql->bound_values[i] = g_malloc0(MDB_BIND_SIZE);
		mdb_sql_bind_column(sql, i+1, sql->bound_values[i], NULL);
	}
}
