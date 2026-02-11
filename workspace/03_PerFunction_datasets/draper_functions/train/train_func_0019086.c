gfm_server_user_info_get_all(struct peer *peer, int from_client, int skip)
{
	gfarm_error_t e;
	struct gfp_xdr *client = peer_get_conn(peer);
	struct gfarm_hash_iterator it;
	gfarm_int32_t nusers;
	struct user **u;
	static const char diag[] = "GFM_PROTO_USER_INFO_GET_ALL";

	if (skip)
		return (GFARM_ERR_NO_ERROR);


	giant_lock();

	nusers = 0;
	for (gfarm_hash_iterator_begin(user_hashtab, &it);
	     !gfarm_hash_iterator_is_end(&it);
	     gfarm_hash_iterator_next(&it)) {
		u = gfarm_hash_entry_data(gfarm_hash_iterator_access(&it));
		if (user_is_active(*u))
			++nusers;
	}
	e = gfm_server_put_reply(peer, diag,
	    GFARM_ERR_NO_ERROR, "i", nusers);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1001498,
			"gfm_server_put_reply() failed: %s",
			gfarm_error_string(e));
		giant_unlock();
		return (e);
	}
	for (gfarm_hash_iterator_begin(user_hashtab, &it);
	     !gfarm_hash_iterator_is_end(&it);
	     gfarm_hash_iterator_next(&it)) {
		u = gfarm_hash_entry_data(gfarm_hash_iterator_access(&it));
		if (user_is_active(*u)) {
			e = user_info_send(client, &(*u)->ui);
			if (e != GFARM_ERR_NO_ERROR) {
				gflog_debug(GFARM_MSG_1001499,
					"user_info_send() failed: %s",
					gfarm_error_string(e));
				giant_unlock();
				return (e);
			}
		}
	}

	giant_unlock();
	return (GFARM_ERR_NO_ERROR);
}
