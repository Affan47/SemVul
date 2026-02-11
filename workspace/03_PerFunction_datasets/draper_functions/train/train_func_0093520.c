save_results_cb (GtkWidget * chooser,
                 gint response,
                 gpointer data)
{
	GSearchWindow * gsearch = data;
	GtkListStore * store;
	GtkTreeIter iter;
	FILE * fp;
	gchar * utf8 = NULL;

	if (response != GTK_RESPONSE_OK) {
		gtk_widget_destroy (GTK_WIDGET (chooser));
		return;
	}

	store = gsearch->search_results_list_store;
	g_free (gsearch->save_results_as_default_filename);

	gsearch->save_results_as_default_filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
	gtk_widget_destroy (chooser);

	if (gsearch->save_results_as_default_filename != NULL) {
		utf8 = g_filename_to_utf8 (gsearch->save_results_as_default_filename, -1, NULL, NULL, NULL);
	}

	if (utf8 == NULL) {
		display_dialog_could_not_save_no_name (gsearch->window);
		return;
	}

	if (g_file_test (gsearch->save_results_as_default_filename, G_FILE_TEST_IS_DIR)) {
		display_dialog_could_not_save_to (gsearch->window, utf8,
		                                  _("The document name you selected is a folder."));
		g_free (utf8);
		return;
	}

#if !GTK_CHECK_VERSION(2,7,3)
	if (g_file_test (gsearch->save_results_as_default_filename, G_FILE_TEST_EXISTS)) {

		gint response;

		response = display_dialog_could_not_save_exists (gsearch->window, utf8);

		if (response != GTK_RESPONSE_OK) {
			g_free (utf8);
			return;
		}
	}
#endif

	if ((fp = fopen (gsearch->save_results_as_default_filename, "w")) != NULL) {

		gint idx;

		for (idx = 0; idx < gtk_tree_model_iter_n_children (GTK_TREE_MODEL (store), NULL); idx++)
		{
			if (gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (store), &iter, NULL, idx) == TRUE) {

				gchar * locale_file;

				gtk_tree_model_get (GTK_TREE_MODEL (store), &iter, COLUMN_LOCALE_FILE, &locale_file, -1);
				fprintf (fp, "%s\n", locale_file);
				g_free (locale_file);
			}
		}
		fclose (fp);
	}
	else {
		display_dialog_could_not_save_to (gsearch->window, utf8,
		                                  _("You may not have write permissions to the document."));
	}
	g_free (utf8);
}
