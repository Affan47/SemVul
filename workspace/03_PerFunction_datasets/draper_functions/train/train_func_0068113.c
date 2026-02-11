maki_channel_remove_users (makiChannel* chan)
{
	GHashTableIter iter;
	gpointer key, value;

	if (g_hash_table_size(chan->users) == 0)
	{
		return;
	}

	g_hash_table_iter_init(&iter, chan->users);

	while (g_hash_table_iter_next(&iter, &key, &value))
	{
		makiUser* user = value;

		maki_server_remove_user(chan->server, maki_user_nick(user));
	}

	g_hash_table_remove_all(chan->user_prefixes);
	g_hash_table_remove_all(chan->users);
}
