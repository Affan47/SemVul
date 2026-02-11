db_table_deref(db_table* entry){
	DEBUG("[#] Decrementing table refcount - was: %d\n", entry->refs);
	assert(entry->refs > 0);
	entry->refs--;


	if (entry->refs == 0 && entry->deleted){

		db_table_actually_delete(entry);
	}
}
