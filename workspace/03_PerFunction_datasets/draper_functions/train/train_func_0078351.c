gfm_server_quota_check(struct peer *peer, int from_client, int skip)
{
	static const char diag[] = "GFM_PROTO_QUOTA_CHECK";
	gfarm_error_t e;
	struct user *peer_user = peer_get_user(peer);

	e = gfm_server_get_request(peer, diag, "");
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002063,
			"%s request failed: %s", diag, gfarm_error_string(e));
		return (e);
	}
	if (skip)
		return (GFARM_ERR_NO_ERROR);

	if (db_state != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002064, "db_quota is invalid: %s",
			gfarm_error_string(db_state));
		return (gfm_server_put_reply(peer, diag, db_state, ""));
	}

	giant_lock();
	if (!from_client || peer_user == NULL || !user_is_admin(peer_user)) {
		giant_unlock();
		e = GFARM_ERR_OPERATION_NOT_PERMITTED;
		gflog_debug(GFARM_MSG_1002065,
			    "%s: !from_client or invalid peer_user"
			    " or !user_is_admin", diag);
		return (gfm_server_put_reply(peer, diag, e, ""));
	}

	quota_clear_value_all_user_and_group();

	inode_lookup_all(NULL, quota_update_file_add_for_quotacheck);

	quota_set_value_all_user_and_group();
	giant_unlock();

	return (gfm_server_put_reply(peer, diag, e, ""));
}
