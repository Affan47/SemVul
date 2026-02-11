dispose_db(struct db *db)
{
    if (!db) return 0;

    if (db->lock_status) {
	syslog(LOG_ERR, "skiplist: closed while still locked");
	unlock(db);
    }
    if (db->fname) {
	free(db->fname);
    }
    if (db->map_base) {
	map_free(&db->map_base, &db->map_len);
    }
    if (db->fd != -1) {
	close(db->fd);
    }

    free(db);

    return 0;
}
