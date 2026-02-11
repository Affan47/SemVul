read_server_setup(gint fd)
	{
	gchar			buf[4097];
	gint			table_size;

	gkrellm_debug(DEBUG_CLIENT, "read_server_setup()\n");


	locale_sync();
	_GK.client_server_read_time = time(0);
	table_size = sizeof(setup_table) / sizeof(KeyTable);

	gkrellm_free_glist_and_data(&client_plugin_setup_line_list);

    gint rs;

	while (1)
		{
		rs = gkrellm_getline(fd, buf, sizeof(buf));
        if (rs < 0)
            return FALSE;
		if (!strcmp(buf, "</gkrellmd_setup>"))
			break;
		process_server_line(&setup_table[0], table_size, buf);
		}


	client_inet_reset();


	table_size = sizeof(update_table) / sizeof(KeyTable);
	while (1)
		{
		rs = gkrellm_getline(fd, buf, sizeof(buf));
        if (rs < 0)
            return FALSE;
		if (!strcmp(buf, "</initial_update>"))
			break;
		process_server_line(&update_table[0], table_size, buf);
		}
	setup_done = TRUE;
    return TRUE;
	}
