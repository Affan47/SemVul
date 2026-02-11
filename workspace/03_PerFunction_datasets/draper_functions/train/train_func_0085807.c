dico_udb_open(dico_udb_t db)
{
    if (!db)
	return 1;
    if (!db->_db_open)
	return 0;
    return db->_db_open(&db->handle, db->url, db->options);
}
