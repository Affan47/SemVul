check_server_splits(IRC_SERVER_REC *server)
{
	time_t last;

	g_return_val_if_fail(IS_IRC_SERVER(server), FALSE);

	last = get_last_split(server);
	if (time(NULL)-last < SPLIT_WAIT_TIME)
		return FALSE;

	print_splits(server);
        return TRUE;
}
