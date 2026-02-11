myopen(const char *fname, DBTYPE type, int flags, struct db **ret)
{
    DB *db = NULL;
    int r;
    int dbflags = (flags & CYRUSDB_CREATE) ? DB_CREATE : 0;

    assert(dbinit && fname && ret);

    *ret = NULL;

    r = db_create(&db, dbenv, 0);
    if (r != 0) {
	syslog(LOG_ERR, "DBERROR: opening %s (creating database handle): %s", fname, db_strerror(r));
	return CYRUSDB_IOERROR;
    }

    if (flags & CYRUSDB_MBOXSORT) db->set_bt_compare(db, mbox_compar);

#if ((DB_VERSION_MAJOR > 4) || ((DB_VERSION_MAJOR == 4) && (DB_VERSION_MINOR >= 1)))
    r = (db->open)(db, NULL, fname, NULL, type, dbflags | DB_AUTO_COMMIT, 0664);
#else
    r = (db->open)(db, fname, NULL, type, dbflags, 0664);
#endif

    if (r != 0) {
	int level = (flags & CYRUSDB_CREATE) ? LOG_ERR : LOG_DEBUG;
	syslog(level, "DBERROR: opening %s: %s", fname, db_strerror(r));
	r = (db->close)(db, DB_NOSYNC);
        if (r != 0) {
            syslog(level, "DBERROR: closing %s: %s", fname, db_strerror(r));
        }
	return CYRUSDB_IOERROR;
    }

    *ret = (struct db *) db;

    return r;
}
