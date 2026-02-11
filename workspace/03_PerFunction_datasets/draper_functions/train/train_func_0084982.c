prompter_method_begin_prompting (GcrSystemPrompter *self,
                                 GDBusMethodInvocation *invocation,
                                 GVariant *parameters)
{
	Callback lookup;
	Callback *callback;
	const gchar *caller;
	guint watch_id;

	lookup.name = caller = g_dbus_method_invocation_get_sender (invocation);
	g_variant_get (parameters, "(&o)", &lookup.path);

	_gcr_debug ("received %s call from callback %s@%s",
	            GCR_DBUS_PROMPTER_METHOD_BEGIN,
	            lookup.path, lookup.name);

	if (g_hash_table_lookup (self->pv->callbacks, &lookup)) {
		_gcr_debug ("already begun prompting for callback %s@%s",
		            lookup.path, lookup.name);
		g_dbus_method_invocation_return_error_literal (invocation, G_DBUS_ERROR, G_DBUS_ERROR_FAILED,
		                                               "Already begun prompting for this prompt callback");
		return;
	}

	callback = callback_dup (&lookup);
	watch_id = g_bus_watch_name_on_connection (self->pv->connection, caller,
	                                           G_BUS_NAME_WATCHER_FLAGS_NONE,
	                                           NULL, on_caller_vanished,
	                                           self, NULL);
	g_hash_table_insert (self->pv->callbacks, callback, GUINT_TO_POINTER (watch_id));

	g_dbus_method_invocation_return_value (invocation, g_variant_new ("()"));

	g_queue_push_tail (&self->pv->waiting, callback);
	g_object_notify (G_OBJECT (self), "prompting");

	prompt_next_ready (self);
}
