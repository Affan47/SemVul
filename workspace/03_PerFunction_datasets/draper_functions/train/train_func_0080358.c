myfetch(struct db *mydb,
		   const char *key, int keylen,
		   const char **data, int *datalen,
		   struct txn **mytid, int flags)
{
    int r = 0;
    DBT k, d;
    DB *db = (DB *) mydb;
    DB_TXN *tid = NULL;

    assert(dbinit && db);

    if (data) *data = NULL;
    if (datalen) *datalen = 0;

    r = gettid(mytid, &tid, "myfetch");
    if (r) return r;

    memset(&k, 0, sizeof(k));
    memset(&d, 0, sizeof(d));

    k.data = (char *) key;
    k.size = keylen;

    r = db->get(db, tid, &k, &d, flags);
    switch (r) {
    case 0:
	if (data) *data = d.data;
	if (datalen) *datalen = d.size;
	break;
    case DB_NOTFOUND:
	r = CYRUSDB_NOTFOUND;
	break;
    case DB_LOCK_DEADLOCK:
	if (mytid) {
	    abort_txn(mydb, *mytid);
	    *mytid = NULL;
	}
	r = CYRUSDB_AGAIN;
	break;
    default:
	syslog(LOG_ERR, "DBERROR: error fetching %s: %s", key,
	       db_strerror(r));
	r = CYRUSDB_IOERROR;
	break;
    }

    return r;
}
