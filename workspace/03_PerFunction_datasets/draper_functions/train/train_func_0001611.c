cmd_window_move(const char *data, SERVER_REC *server, WI_ITEM_REC *item)
{
	if (!is_numeric(data, 0)) {
		command_runsub("window move", data, server, item);
                return;
	}

	active_window_move_to(atoi(data));
}
