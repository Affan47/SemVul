cl5GetFirstOperation (Object *replica, slapi_operation_parameters *op, void **iterator)
{
	int rc;
	CL5Entry entry;
    Object *obj;
	char *agmt_name;

	if (replica == NULL || op == NULL || iterator == NULL)
	{
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name_cl,
						"cl5GetFirstOperation: invalid argument\n");
		return CL5_BAD_DATA;
	}

	*iterator = NULL;

	if (s_cl5Desc.dbState == CL5_STATE_NONE)
	{
		agmt_name = get_thread_private_agmtname();
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name_cl,
						"%s: cl5GetFirstOperation: changelog is not initialized\n", agmt_name);
		return CL5_BAD_STATE;
	}


	rc = _cl5AddThread ();
	if (rc != CL5_SUCCESS)
		return rc;

    rc = _cl5GetDBFile (replica, &obj);
	if (rc != CL5_SUCCESS)
	{
        _cl5RemoveThread ();
		return rc;
	}

	entry.op = op;

	rc = _cl5GetFirstEntry (obj, &entry, iterator, NULL);
    object_release (obj);

	_cl5RemoveThread ();

	return rc;
}
