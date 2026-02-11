add_listener (GeditMessageBus      *bus,
              Message		   *message,
              GeditMessageCallback  callback,
              gpointer		    user_data,
              GDestroyNotify        destroy_data)
{
	Listener *listener;
	IdMap *idmap;

	listener = g_slice_new (Listener);
	listener->id = ++bus->priv->next_id;
	listener->callback = callback;
	listener->user_data = user_data;
	listener->blocked = FALSE;
	listener->destroy_data = destroy_data;

	message->listeners = g_list_append (message->listeners, listener);

	idmap = g_new (IdMap, 1);
	idmap->message = message;
	idmap->listener = g_list_last (message->listeners);

	g_hash_table_insert (bus->priv->idmap, GINT_TO_POINTER (listener->id), idmap);

	return listener->id;
}
