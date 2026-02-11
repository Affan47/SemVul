miner_resume (const gchar *miner,
              gint         cookie)
{
	TrackerMinerManager *manager;
	GError *error = NULL;
	gchar *str;


	manager = tracker_miner_manager_new_full (FALSE, &error);
	if (!manager) {
		g_printerr (_("Could not resume miner, manager could not be created, %s"),
		            error ? error->message : "unknown error");
		g_printerr ("\n");
		g_clear_error (&error);
		return EXIT_FAILURE;
	}

	str = g_strdup_printf (_("Attempting to resume miner %s with cookie %d"),
	                       miner,
	                       cookie);
	g_print ("%s\n", str);
	g_free (str);

	if (!tracker_miner_manager_resume (manager, miner, cookie)) {
		g_printerr (_("Could not resume miner: %s"), miner);
		return EXIT_FAILURE;
	}

	g_print ("  %s\n", _("Done"));

	g_object_unref (manager);

	return EXIT_SUCCESS;
}
