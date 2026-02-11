e_ews_connection_get_items_sync (EEwsConnection *cnc,
                                 gint pri,
                                 const GSList *ids,
                                 const gchar *default_props,
                                 const gchar *additional_props,
                                 gboolean include_mime,
                                 const gchar *mime_directory,
				 EEwsBodyType body_type,
                                 GSList **items,
                                 ESoapProgressFn progress_fn,
                                 gpointer progress_data,
                                 GCancellable *cancellable,
                                 GError **error)
{
	EAsyncClosure *closure;
	GAsyncResult *result;
	gboolean success;

	g_return_val_if_fail (cnc != NULL, FALSE);

	closure = e_async_closure_new ();

	e_ews_connection_get_items (
		cnc, pri,ids, default_props,
		additional_props, include_mime,
		mime_directory, body_type, progress_fn,
		progress_data, cancellable,
		e_async_closure_callback, closure);

	result = e_async_closure_wait (closure);

	success = e_ews_connection_get_items_finish (
		cnc, result, items, error);

	e_async_closure_free (closure);

	return success;
}
