database_iterate(dico_list_iterator_t fun, void *data)
{
    dico_iterator_t itr = xdico_list_iterator(database_list);
    dicod_database_t *db;
    int rc = 0;

    for (db = dico_iterator_first(itr); rc == 0 && db;
	 db = dico_iterator_next(itr)) {
	if (database_visible_p(db))
	    rc = fun(db, data);
    }
    dico_iterator_destroy(&itr);
    return rc;
}
