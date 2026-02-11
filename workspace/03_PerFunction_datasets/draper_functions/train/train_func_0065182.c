find_gdb_transport ( const char *name ) {
	struct gdb_transport *trans;

	for_each_table_entry ( trans, GDB_TRANSPORTS ) {
		if ( strcmp ( trans->name, name ) == 0 ) {
			return trans;
		}
	}
	return NULL;
}
