on_prompt_ready_complete (GObject *source,
                          GAsyncResult *result,
                          gpointer user_data)
{
	ActivePrompt *active = user_data;
	GcrSystemPrompter *self = g_object_ref (active->prompter);
	GError *error = NULL;
	GVariant *retval;

	g_assert (active->ready == FALSE);

	_gcr_debug ("returned from the %s method on %s@%s",
	            GCR_DBUS_CALLBACK_METHOD_READY, active->callback->path, active->callback->name);

	active->ready = TRUE;
	retval = g_dbus_connection_call_finish (G_DBUS_CONNECTION (source), result, &error);


	if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED) &&
	    g_cancellable_is_cancelled (active->cancellable)) {
		g_error_free (error);


	} else if (error != NULL) {
		if (g_error_matches (error, G_DBUS_ERROR, G_DBUS_ERROR_UNKNOWN_METHOD))
			_gcr_debug ("prompt %s@%s disappeared or does not exist",
			            active->callback->path, active->callback->name);
		else
			g_message ("received an error from the prompt callback: %s", error->message);
		g_error_free (error);

		prompt_stop_prompting (self, active->callback, FALSE, FALSE);


		prompt_next_ready (self);
	}

	if (retval != NULL)
		g_variant_unref (retval);

	active_prompt_unref (active);
	g_object_unref (self);
}
