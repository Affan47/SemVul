search_files_search_clicked (SearchFiles* sf)
{
	GFile* selected;
	IAnjutaProjectManager* pm;
	GList* files = NULL;
	GList* file;
	gchar* project_uri;
	AnjutaCommandQueue* queue;
	gchar* mime_types;
	GtkComboBox* type_combo;
	GtkTreeIter iter;

	g_return_if_fail (sf != NULL && SEARCH_IS_FILES (sf));


	gtk_list_store_clear(GTK_LIST_STORE (sf->priv->files_model));
	gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE (sf->priv->files_model),
	                                     COLUMN_FILENAME,
	                                     GTK_SORT_DESCENDING);


	selected =
		ianjuta_project_chooser_get_selected(IANJUTA_PROJECT_CHOOSER (sf->priv->project_combo),
		                                     NULL);
	type_combo = GTK_COMBO_BOX (sf->priv->file_type_combo);
	gtk_combo_box_get_active_iter(type_combo, &iter);
	gtk_tree_model_get (gtk_combo_box_get_model (type_combo),
	                    &iter,
	                    COMBO_LANG_TYPES, &mime_types,
	                    -1);


	pm = anjuta_shell_get_interface (sf->priv->docman->shell,
	                                 IAnjutaProjectManager,
	                                 NULL);
	files = ianjuta_project_manager_get_children(pm, selected, ANJUTA_PROJECT_SOURCE, NULL);


	anjuta_shell_get (sf->priv->docman->shell,
	                  IANJUTA_PROJECT_MANAGER_PROJECT_ROOT_URI,
	                  G_TYPE_STRING,
	                  &project_uri, NULL);
	if (sf->priv->project_file)
		g_object_unref (sf->priv->project_file);

	if (project_uri)
	{
		sf->priv->project_file = g_file_new_for_uri (project_uri);
	}
	g_free (project_uri);


	if (files != NULL)
	{

		queue = anjuta_command_queue_new(ANJUTA_COMMAND_QUEUE_EXECUTE_MANUAL);
		g_signal_connect (queue, "finished",
	    	              G_CALLBACK (search_files_filter_finished), sf);
		for (file = files; file != NULL; file = g_list_next (file))
		{
			SearchFilterFileCommand* cmd =
				search_filter_file_command_new(G_FILE (file->data),
			    	                           mime_types);


			if (!g_file_has_prefix (G_FILE (file->data), sf->priv->project_file))
				continue;

			g_signal_connect (cmd, "command-finished",
		    	              G_CALLBACK (search_files_filter_command_finished), sf);
			anjuta_command_queue_push(queue, ANJUTA_COMMAND(cmd));
		}
		sf->priv->busy = TRUE;
		search_files_update_ui(sf);
		anjuta_command_queue_start (queue);

		g_list_foreach (files, (GFunc) g_object_unref, NULL);
		g_list_free (files);
	}

	g_free (mime_types);
}
