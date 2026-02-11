repl5_inc_result_threadmain(void *param)
{
	result_data *rd = (result_data*) param;
	ConnResult conres = 0;
	Repl_Connection *conn = rd->prp->conn;
	int finished = 0;
	int message_id = 0;

	slapi_log_error(SLAPI_LOG_REPL, NULL, "repl5_inc_result_threadmain starting\n");
	while (!finished)
	{
		repl5_inc_operation *op = NULL;
		int connection_error = 0;
		char *csn_str = NULL;
		char *uniqueid = NULL;
		ReplicaId replica_id = 0;
		int operation_code = 0;
		char *ldap_error_string = NULL;
		time_t time_now = 0;
		time_t start_time = time( NULL );
		int backoff_time = 1;


		while (!finished)
		{
			conres = conn_read_result_ex(conn, NULL, NULL, NULL, LDAP_RES_ANY, &message_id, 0);
			slapi_log_error(SLAPI_LOG_REPL, NULL, "repl5_inc_result_threadmain: read result for message_id %d\n", message_id);

			if (CONN_TIMEOUT == conres)
			{


				time_now = time( NULL );
				if (conn_get_timeout(conn) <= ( time_now - start_time ))
				{

					conres = CONN_TIMEOUT;
					break;
				}

				DS_Sleep(PR_MillisecondsToInterval(backoff_time));
				if (backoff_time < 1000)
				{
					backoff_time <<= 1;
				}

				PR_Lock(rd->lock);
				if (rd->stop_result_thread)
				{
					finished = 1;
				}
				PR_Unlock(rd->lock);
			} else
			{

				break;
			}
		}
		if (conres != CONN_TIMEOUT)
		{
			int return_value;
			int should_finish = 0;
			if (message_id)
			{
				rd->last_message_id_received = message_id;
			}


			op = repl5_inc_pop_operation(rd);
			if (op)
			{
				csn_str = op->csn_str;
				replica_id = op->replica_id;
				uniqueid = op->uniqueid;
			}

			conn_get_error_ex(conn, &operation_code, &connection_error, &ldap_error_string);
			slapi_log_error(SLAPI_LOG_REPL, NULL, "repl5_inc_result_threadmain: result %d, %d, %d, %d, %s\n", operation_code,connection_error,conres,message_id,ldap_error_string);
			return_value = repl5_inc_update_from_op_result(rd->prp, conres, connection_error, csn_str, uniqueid, replica_id, &should_finish, &(rd->num_changes_sent));
			if (return_value || should_finish)
			{
				slapi_log_error(SLAPI_LOG_REPL, NULL, "repl5_inc_result_threadmain: got op result %d should finish %d\n", return_value, should_finish);

				PR_Lock(rd->lock);
				rd->result = return_value;
				rd->abort = 1;
				PR_Unlock(rd->lock);


				if (return_value == UPDATE_CONNECTION_LOST) {
					finished = 1;
				}
			} else {

				rd->result = return_value;
			}
		}

		PR_Lock(rd->lock);
		if (rd->stop_result_thread)
		{
			finished = 1;
		}
		PR_Unlock(rd->lock);
		if (op)
		{
			repl5_inc_op_free(op);
		}
	}
	slapi_log_error(SLAPI_LOG_REPL, NULL, "repl5_inc_result_threadmain exiting\n");
}
