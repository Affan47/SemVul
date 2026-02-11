miner_list (gboolean available,
            gboolean running)
{
	TrackerMinerManager *manager;
	GError *error = NULL;


	manager = tracker_miner_manager_new_full (FALSE, &error);
	if (!manager) {
		g_printerr (_("Could not list miners, manager could not be created, %s"),
		            error ? error->message : "unknown error");
		g_printerr ("\n");
		g_clear_error (&error);
		return EXIT_FAILURE;
	}

	if (available) {
		GSList *miners_available;
		gchar *str;
		GSList *l;

		miners_available = tracker_miner_manager_get_available (manager);

		str = g_strdup_printf (ngettext ("Found %d miner installed",
		                                 "Found %d miners installed",
		                                 g_slist_length (miners_available)),
		                       g_slist_length (miners_available));

		g_print ("%s%s\n", str, g_slist_length (miners_available) > 0 ? ":" : "");
		g_free (str);

		for (l = miners_available; l; l = l->next) {
			g_print ("  %s\n", (gchar*) l->data);
		}

		g_slist_foreach (miners_available, (GFunc) g_free, NULL);
		g_slist_free (miners_available);
	}

	if (running) {
		GSList *miners_running;
		gchar *str;
		GSList *l;

		miners_running = tracker_miner_manager_get_running (manager);

		str = g_strdup_printf (ngettext ("Found %d miner running",
		                                 "Found %d miners running",
		                                 g_slist_length (miners_running)),
		                       g_slist_length (miners_running));

		g_print ("%s%s\n", str, g_slist_length (miners_running) > 0 ? ":" : "");
		g_free (str);

		for (l = miners_running; l; l = l->next) {
			g_print ("  %s\n", (gchar*) l->data);
		}

		g_slist_foreach (miners_running, (GFunc) g_free, NULL);
		g_slist_free (miners_running);
	}

	g_object_unref (manager);

	return EXIT_SUCCESS;
}
