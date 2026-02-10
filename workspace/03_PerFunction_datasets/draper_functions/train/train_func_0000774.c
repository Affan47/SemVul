cyrusdb_convert(const char *fromfname, const char *tofname,
		     struct cyrusdb_backend *frombackend,
		     struct cyrusdb_backend *tobackend)
{
    struct db *fromdb, *todb;
    struct convert_rock cr;
    struct txn *fromtid = NULL;
    int r;


    r = (frombackend->open)(fromfname, 0, &fromdb);
    if (r != CYRUSDB_OK)
	fatal("can't open old database", EC_TEMPFAIL);
    r = (tobackend->open)(tofname, CYRUSDB_CREATE, &todb);
    if (r != CYRUSDB_OK)
	fatal("can't open new database", EC_TEMPFAIL);


    cr.backend = tobackend;
    cr.db = todb;
    cr.tid = NULL;


    (frombackend->foreach)(fromdb, "", 0, NULL, converter_cb, &cr, &fromtid);


    if (fromtid) (frombackend->commit)(fromdb, fromtid);
    if (cr.tid) (tobackend->commit)(todb, cr.tid);


    (frombackend->close)(fromdb);
    (tobackend->close)(todb);
}
