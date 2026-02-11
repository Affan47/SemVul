quota_read(struct quota *quota, struct txn **tid, int wrlock)
{
    int r;
    int qrlen;
    const char *data;
    int datalen;

    if (!quota->root || !(qrlen = strlen(quota->root)))
	return IMAP_QUOTAROOT_NONEXISTENT;

    if (wrlock)
	r = QDB->fetchlock(qdb, quota->root, qrlen, &data, &datalen, tid);
    else
	r = QDB->fetch(qdb, quota->root, qrlen, &data, &datalen, tid);

    if (!datalen)
	return IMAP_QUOTAROOT_NONEXISTENT;

    switch (r) {
    case CYRUSDB_OK:
	if (!*data) return IMAP_QUOTAROOT_NONEXISTENT;
	if (!quota_parseval(data, quota)) {
	    syslog(LOG_ERR, "DBERROR: error fetching quota "
			    "root=<%s> value=<%s>",
		   quota->root, data);
	    return CYRUSDB_IOERROR;
	}
	break;

    case CYRUSDB_AGAIN:
	return IMAP_AGAIN;
	break;

    case CYRUSDB_NOTFOUND:
	return IMAP_QUOTAROOT_NONEXISTENT;
	break;
    }

    if (r) {
	syslog(LOG_ERR, "DBERROR: error fetching quota %s: %s",
	       quota->root, cyrusdb_strerror(r));
	return IMAP_IOERROR;
    }

    return 0;
}
