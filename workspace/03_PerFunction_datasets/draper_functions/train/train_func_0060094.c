isns_process_query(isns_server_t *srv, isns_simple_t *call, isns_simple_t **result)
{
	isns_object_list_t	objects = ISNS_OBJECT_LIST_INIT;
	isns_simple_t		*reply = NULL;
	isns_db_t		*db = srv->is_db;
	int			status;


	status = isns_query_get_objects(call, db, &objects);
	if (status != ISNS_SUCCESS)
		goto done;


	reply = isns_create_query_response(srv, call, &objects);
	if (reply == NULL) {
		status = ISNS_INTERNAL_ERROR;
		goto done;
	}


	if (objects.iol_count == 0) {
		status = ISNS_NO_SUCH_ENTRY;
		goto done;
	}

done:
	isns_object_list_destroy(&objects);
	*result = reply;
	return status;
}
