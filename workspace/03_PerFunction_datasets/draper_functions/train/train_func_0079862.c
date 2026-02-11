__repmgr_destroy_conn(env, conn)
	ENV *env;
	REPMGR_CONNECTION *conn;
{
	QUEUED_OUTPUT *out;
	REPMGR_FLAT *msg;
	REPMGR_RESPONSE *resp;
	DBT *dbt;
	int ret, t_ret;

	ret = 0;

	DB_ASSERT(env, conn->ref_count == 0);


	if (conn->reading_phase == DATA_PHASE) {
		switch (conn->msg_type) {
		case REPMGR_OWN_MSG:
			if (conn->input.rep_message == NULL)
				break;

		case REPMGR_APP_MESSAGE:
		case REPMGR_HEARTBEAT:
		case REPMGR_REP_MESSAGE:
			__os_free(env, conn->input.rep_message);
			break;

		case REPMGR_APP_RESPONSE:


			DB_ASSERT(env, conn->cur_resp < conn->aresp &&
			    conn->responses != NULL);
			resp = &conn->responses[conn->cur_resp];
			DB_ASSERT(env, F_ISSET(resp, RESP_READING));
			if (F_ISSET(resp, RESP_DUMMY_BUF))
				__os_free(env, resp->dbt.data);
			break;

		case REPMGR_PERMLSN:
		case REPMGR_HANDSHAKE:
			dbt = &conn->input.repmgr_msg.cntrl;
			if (dbt->size > 0)
				__os_free(env, dbt->data);
			dbt = &conn->input.repmgr_msg.rec;
			if (dbt->size > 0)
				__os_free(env, dbt->data);
			break;

		case REPMGR_RESP_ERROR:


		default:
			ret = __db_unknown_path(env, "destroy_conn");
		}
	}

	if (conn->type == APP_CONNECTION && conn->responses != NULL)
		__os_free(env, conn->responses);

	if ((t_ret = __repmgr_destroy_waiters(env,
		    &conn->response_waiters)) != 0 && ret == 0)
		ret = t_ret;

	while (!STAILQ_EMPTY(&conn->outbound_queue)) {
		out = STAILQ_FIRST(&conn->outbound_queue);
		STAILQ_REMOVE_HEAD(&conn->outbound_queue, entries);
		msg = out->msg;
		if (--msg->ref_count <= 0)
			__os_free(env, msg);
		__os_free(env, out);
	}
	if ((t_ret = __repmgr_free_cond(&conn->drained)) != 0 &&
	    ret == 0)
		ret = t_ret;

	__os_free(env, conn);
	return (ret);
}
