item_put(char *key, size_t nkey, item *it){
    int ret;
    DBT dbkey, dbdata;

    BDB_CLEANUP_DBT();
    dbkey.data = key;
    dbkey.size = nkey;
    dbdata.data = it;
    dbdata.size = ITEM_ntotal(it);
    ret = dbp->put(dbp, NULL, &dbkey, &dbdata, 0);
    if (ret == 0) {
        return 0;
    } else {
        if (settings.verbose > 1) {
            fprintf(stderr, "dbp->put: %s\n", db_strerror(ret));
        }
        return -1;
    }
}
