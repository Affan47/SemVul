cal_client_view_complete_cb (EGdbusCalView *dbus_proxy,
                             const gchar * const *arg_error,
                             GWeakRef *client_view_weak_ref)
{
	ECalClientView *client_view;

	client_view = g_weak_ref_get (client_view_weak_ref);

	if (client_view != NULL) {
		GSource *idle_source;
		GMainContext *main_context;
		SignalClosure *signal_closure;

		if (!client_view->priv->running) {
			g_object_unref (client_view);
			return;
		}

		signal_closure = g_slice_new0 (SignalClosure);
		g_weak_ref_set (&signal_closure->client_view, client_view);
		e_gdbus_templates_decode_error (
			arg_error, &signal_closure->error);

		main_context = cal_client_view_ref_main_context (client_view);

		idle_source = g_idle_source_new ();
		g_source_set_callback (
			idle_source,
			cal_client_view_emit_complete_idle_cb,
			signal_closure,
			(GDestroyNotify) signal_closure_free);
		g_source_attach (idle_source, main_context);
		g_source_unref (idle_source);

		g_main_context_unref (main_context);

		g_object_unref (client_view);
	}
}
