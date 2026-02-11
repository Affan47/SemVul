statuscache_invalidate(const char *mboxname, struct statusdata *sdata)
{
    int keylen, r;
    char *key;
    int doclose = 0;
    struct statuscache_deleterock drock;


    if (!config_getswitch(IMAPOPT_STATUSCACHE))
	return 0;


    if (!statuscache_dbopen) {
	statuscache_open(NULL);
	doclose = 1;
    }

    drock.db = statuscachedb;
    drock.tid = NULL;

    key = statuscache_buildkey(mboxname, NULL, &keylen);

    r = DB->foreach(drock.db, key, keylen, NULL, delete_cb,
		    &drock, &drock.tid);
    if (r != CYRUSDB_OK) {
	syslog(LOG_ERR, "DBERROR: error invalidating: %s (%s)",
	       mboxname, cyrusdb_strerror(r));
    }

    if (!r && sdata) {
	r = statuscache_update_txn(mboxname, sdata, &drock.tid);
    }

    if (r != CYRUSDB_OK)
	DB->abort(drock.db, drock.tid);
    else
	DB->commit(drock.db, drock.tid);

    if (doclose)
	statuscache_close();

    return 0;
}
