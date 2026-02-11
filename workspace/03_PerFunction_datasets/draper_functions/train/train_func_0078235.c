write_header(struct db *db)
{
    char buf[HEADER_SIZE];
    int n;

    assert (db->lock_status == WRITELOCKED);
    memcpy(buf + 0, HEADER_MAGIC, HEADER_MAGIC_SIZE);
    *((uint32_t *)(buf + OFFSET_VERSION)) = htonl(db->version);
    *((uint32_t *)(buf + OFFSET_VERSION_MINOR)) = htonl(db->version_minor);
    *((uint32_t *)(buf + OFFSET_MAXLEVEL)) = htonl(db->maxlevel);
    *((uint32_t *)(buf + OFFSET_CURLEVEL)) = htonl(db->curlevel);
    *((uint32_t *)(buf + OFFSET_LISTSIZE)) = htonl(db->listsize);
    *((uint32_t *)(buf + OFFSET_LOGSTART)) = htonl(db->logstart);
    *((uint32_t *)(buf + OFFSET_LASTRECOVERY)) = htonl(db->last_recovery);


    lseek(db->fd, 0, SEEK_SET);
    n = retry_write(db->fd, buf, HEADER_SIZE);
    if (n != HEADER_SIZE) {
	syslog(LOG_ERR, "DBERROR: writing skiplist header for %s: %m",
	       db->fname);
	return CYRUSDB_IOERROR;
    }

    return 0;
}
