statuscache_update_txn(const char *mboxname,
				  struct statusdata *sdata,
				  struct txn **tidptr)
{
    char data[250];
    int keylen, datalen;
    char *key = statuscache_buildkey(mboxname, sdata->userid, &keylen);
    int r;


    if (!statuscache_dbopen)
	return 0;


    datalen = snprintf(data, sizeof(data),
		       "%u %u %u %u %u %u %u " MODSEQ_FMT " ",
		       STATUSCACHE_VERSION,
		       sdata->statusitems, sdata->messages,
		       sdata->recent, sdata->uidnext,
		       sdata->uidvalidity, sdata->unseen,
		       sdata->highestmodseq);

    r = DB->store(statuscachedb, key, keylen, data, datalen, tidptr);

    if (r != CYRUSDB_OK) {
	syslog(LOG_ERR, "DBERROR: error updating database: %s (%s)",
	       mboxname, cyrusdb_strerror(r));
    }

    return r;
}
