source_selector_write_done_cb (GObject *source_object,
                               GAsyncResult *result,
                               gpointer user_data)
{
	ESource *source;
	ESourceSelector *selector;
	GError *error = NULL;

	source = E_SOURCE (source_object);
	selector = E_SOURCE_SELECTOR (user_data);

	e_source_write_finish (source, result, &error);


	if (error != NULL) {
		g_warning ("%s: %s", G_STRFUNC, error->message);
		g_error_free (error);
	}

	g_object_unref (selector);
}
