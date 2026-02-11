gfp_conn_hash_enter(struct gfarm_hash_table **hashtabp, int hashtabsize,
	size_t entrysize,
	const char *hostname, int port, const char *username,
	struct gfarm_hash_entry **entry_ret, int *created_ret)
{
	gfarm_error_t e;
	struct gfp_conn_hash_id id, *idp;
	struct gfarm_hash_entry *entry;
	int created;

	if (*hashtabp == NULL &&
	    (e = gfp_conn_hash_table_init(hashtabp, hashtabsize))
	    != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1001082,
			"initialization of connection hashtable (%d) failed: %s",
			hashtabsize,
			gfarm_error_string(e));
		return (e);
	}

	id.hostname = (char *)hostname;
	id.port = port;
	id.username = (char *)username;
	entry = gfarm_hash_enter(*hashtabp, &id, sizeof(id), entrysize,
	    &created);
	if (entry == NULL) {
		gflog_debug(GFARM_MSG_1001083,
			"insertion to hashtable (%zd) failed: %s",
			entrysize,
			gfarm_error_string(GFARM_ERR_NO_MEMORY));
		return (GFARM_ERR_NO_MEMORY);
	}

	if (created) {
		idp = gfarm_hash_entry_key(entry);
		idp->hostname = strdup(hostname);
		idp->username = strdup(username);
		if (idp->hostname == NULL || idp->username == NULL) {
			if (idp->hostname != NULL)
				free(idp->hostname);
			if (idp->username != NULL)
				free(idp->username);
			idp->hostname = (char *)hostname;
			idp->username = (char *)username;
			gfarm_hash_purge(*hashtabp, &id, sizeof(id));
			gflog_debug(GFARM_MSG_1001084,
				"allocation of hostname or username failed: %s",
				gfarm_error_string(GFARM_ERR_NO_MEMORY));
			return (GFARM_ERR_NO_MEMORY);
		}
	}

	*entry_ret = entry;
	*created_ret = created;
	return (GFARM_ERR_NO_ERROR);
}
