get_supported_fields_reply (GObject *source_object,
                            GAsyncResult *result,
                            gpointer user_data)
{
	AsyncData *data = user_data;
	EBookEListCallback cb = data->callback;
	EBookEListAsyncCallback excb = data->excallback;
	EList *elist;
	gchar *prop_value = NULL;
	GError *error = NULL;

	e_client_get_backend_property_finish (
		E_CLIENT (source_object), result, &prop_value, &error);


	g_return_if_fail (
		((prop_value != NULL) && (error == NULL)) ||
		((prop_value == NULL) && (error != NULL)));


	elist = e_list_new (NULL, (EListFreeFunc) g_free, NULL);

	if (prop_value != NULL) {
		gchar **strv;
		gint ii;

		strv = g_strsplit (prop_value, ",", -1);
		for (ii = 0; strv != NULL && strv[ii] != NULL; ii++) {
			gchar *utf8 = e_util_utf8_make_valid (strv[ii]);
			e_list_append (elist, utf8);
		}
		g_strfreev (strv);
	}

	if (cb != NULL && error == NULL)
		cb (data->book, E_BOOK_ERROR_OK, elist, data->closure);
	if (cb != NULL && error != NULL)
		cb (data->book, error->code, elist, data->closure);
	if (excb != NULL)
		excb (data->book, error, elist, data->closure);

	g_object_unref (elist);

	if (error != NULL)
		g_error_free (error);

	g_object_unref (data->book);
	g_slice_free (AsyncData, data);
}
