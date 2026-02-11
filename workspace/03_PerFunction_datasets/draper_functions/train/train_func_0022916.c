astdb_init(void)
{
	if (db_init()) {
		return -1;
	}

	ast_cond_init(&dbcond, NULL);
	if (ast_pthread_create_background(&syncthread, NULL, db_sync_thread, NULL)) {
		return -1;
	}

	ast_register_atexit(astdb_atexit);
	ast_cli_register_multiple(cli_database, ARRAY_LEN(cli_database));
	ast_manager_register_xml_core("DBGet", EVENT_FLAG_SYSTEM | EVENT_FLAG_REPORTING, manager_dbget);
	ast_manager_register_xml_core("DBPut", EVENT_FLAG_SYSTEM, manager_dbput);
	ast_manager_register_xml_core("DBDel", EVENT_FLAG_SYSTEM, manager_dbdel);
	ast_manager_register_xml_core("DBDelTree", EVENT_FLAG_SYSTEM, manager_dbdeltree);
	return 0;
}
