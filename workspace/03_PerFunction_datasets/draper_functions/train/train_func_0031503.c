connection_passive_lookup_by_ids(u_int8_t *id1, u_int8_t *id2)
{
	struct connection_passive *conn;

	for (conn = TAILQ_FIRST(&connections_passive); conn;
	    conn = TAILQ_NEXT(conn, link)) {
		if (!conn->remote_id)
			continue;


		if ((compare_ids(id1, conn->local_id, conn->local_sz) == 0 &&
		    compare_ids(id2, conn->remote_id, conn->remote_sz) == 0) ||
		    (compare_ids(id1, conn->remote_id, conn->remote_sz) == 0 &&
		    compare_ids(id2, conn->local_id, conn->local_sz) == 0)) {
			LOG_DBG((LOG_MISC, 60,
			    "connection_passive_lookup_by_ids: "
			    "returned \"%s\"", conn->name));
			return conn->name;
		}
	}


	for (conn = TAILQ_FIRST(&connections_passive); conn;
	    conn = TAILQ_NEXT(conn, link)) {
		if (!conn->remote_id)
			continue;

		if (compare_ids(id1, conn->local_id, conn->local_sz) == 0 ||
		    compare_ids(id2, conn->local_id, conn->local_sz) == 0) {
			LOG_DBG((LOG_MISC, 60,
			    "connection passive_lookup_by_ids: returned \"%s\""
			    " only matched local id", conn->name));
			return conn->name;
		}
	}
	LOG_DBG((LOG_MISC, 60,
	    "connection_passive_lookup_by_ids: no match"));
	return 0;
}
