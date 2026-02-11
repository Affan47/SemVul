async_inited (GObject *source, GAsyncResult *result, gpointer user_data)
{
	NMObjectTypeAsyncData *async_data = user_data;
	GObject *object = G_OBJECT (source);
	GError *error = NULL;

	if (!g_async_initable_init_finish (G_ASYNC_INITABLE (object), result, &error)) {
		g_warning ("Could not create object for %s: %s",
		           nm_object_or_connection_get_path (object), error->message);
		g_error_free (error);
		g_object_unref (object);
		object = NULL;
	}

	create_async_complete (object, async_data);
}
