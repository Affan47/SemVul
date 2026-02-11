maki_server_add_channel (makiServer* serv, gchar const* name, makiChannel* chan)
{
	g_return_if_fail(serv != NULL);
	g_return_if_fail(name != NULL);
	g_return_if_fail(chan != NULL);

	g_mutex_lock(serv->mutex.channels);
	g_hash_table_insert(serv->channels, g_strdup(name), chan);
	g_mutex_unlock(serv->mutex.channels);
}
