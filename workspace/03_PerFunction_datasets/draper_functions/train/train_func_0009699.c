db_process(database_handle_t *db, const char *type)
{
	database_handler_f fun;

	return_if_fail(db_types != NULL);
	return_if_fail(db != NULL);
	return_if_fail(type != NULL);

	fun = mowgli_patricia_retrieve(db_types, type);

	if (!fun)
	{
		fun = mowgli_patricia_retrieve(db_types, "???");
	}

	fun(db, type);
}
