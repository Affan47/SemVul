conn_close_admin(uint32_t tid, uint64_t sid, uint32_t cid)
{
	struct iscsi_target* target = NULL;
	struct iscsi_session *session;
	struct iscsi_connection *conn;
	int sess_found = 0;

	target = target_find_by_id(tid);
	if (!target)
		return TGTADM_NO_TARGET;

	list_for_each_entry(session, &target->sessions_list, slist) {
		if (session->tsih == sid) {
			sess_found = 1;
			list_for_each_entry(conn, &session->conn_list, clist) {
				if (conn->cid == cid) {
					eprintf("close %" PRIx64 " %u\n", sid, cid);
					conn->tp->ep_force_close(conn);
					return TGTADM_SUCCESS;
				}
			}
		}
	}

	return sess_found ? TGTADM_NO_CONNECTION : TGTADM_NO_SESSION;
}
