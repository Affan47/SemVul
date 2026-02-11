gck_session_open_finish (GAsyncResult *result,
                         GError **error)
{
	GObject *ret;
	GObject *source;

	source = g_async_result_get_source_object (result);
	ret = g_async_initable_new_finish (G_ASYNC_INITABLE (source), result, error);
	g_object_unref (source);

	return ret ? GCK_SESSION (ret) : NULL;
}
