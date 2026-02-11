pk_control_signal_cb (GDBusProxy *proxy,
		      const gchar *sender_name,
		      const gchar *signal_name,
		      GVariant *parameters,
		      gpointer user_data)
{
	const gchar **ids_tmp = NULL;
	gchar **ids = NULL;
	PkControl *control = PK_CONTROL (user_data);

	if (g_strcmp0 (signal_name, "TransactionListChanged") == 0) {
		g_variant_get (parameters, "(^a&s)", &ids_tmp);
		if (ids_tmp == NULL) {
			ids = g_new0 (gchar *, 1);
		} else {
			ids = g_strdupv ((gchar **) ids_tmp);
		}
		g_debug ("emit transaction-list-changed");
		g_signal_emit (control,
			       signals[SIGNAL_TRANSACTION_LIST_CHANGED], 0,
			       ids);
	}
	if (g_strcmp0 (signal_name, "UpdatesChanged") == 0) {
		g_debug ("emit updates-changed");
		g_signal_emit (control, signals[SIGNAL_UPDATES_CHANGED], 0);
		goto out;
	}
	if (g_strcmp0 (signal_name, "RepoListChanged") == 0) {
		g_debug ("emit repo-list-changed");
		g_signal_emit (control, signals[SIGNAL_REPO_LIST_CHANGED], 0);
		goto out;
	}
	if (g_strcmp0 (signal_name, "Changed") == 0) {

		goto out;
	}
	if (g_strcmp0 (signal_name, "RestartSchedule") == 0) {
		g_debug ("emit restart-schedule");
		g_signal_emit (control, signals[SIGNAL_RESTART_SCHEDULE], 0);
		goto out;
	}
out:
	g_free (ids_tmp);
	g_strfreev (ids);
}
