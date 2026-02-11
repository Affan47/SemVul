master_position_provider_changed (GeoclueMasterClient *client,
                                  char *name,
                                  char *description,
                                  char *service,
                                  char *path,
                                  GeoclueTestGui *gui)
{
	GtkTreeIter iter;
	char *msg;

	if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (gui->position_store),
					   &iter)) {
		gtk_list_store_set (gui->position_store, &iter,
				    COL_POSITION_PROVIDER_NAME, g_strdup_printf ("Master (%s)", name),
				    -1);
	}
	msg = g_strdup_printf ("Master: position provider changed: %s", name);
	geoclue_test_gui_master_log_message (gui, msg);
	g_free (msg);
}
