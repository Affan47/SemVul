isns_end_write_operation(isns_server_t *srv, isns_simple_t *msg, int *status)
{
	if (*status == ISNS_SUCCESS)
		isns_db_commit(srv->is_db);
	else
		isns_db_rollback(srv->is_db);
}
