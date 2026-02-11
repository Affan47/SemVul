server_idle_remove(IRC_SERVER_REC *server, int tag)
{
	SERVER_IDLE_REC *rec;

	g_return_val_if_fail(server != NULL, FALSE);

	rec = server_idle_find_rec(server, tag);
	if (rec == NULL)
		return FALSE;

	server_idle_destroy(server, rec);
	return TRUE;
}
