uninstall_scheme_clicked (GtkButton              *button,
			  GeditPreferencesDialog *dlg)
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (dlg->priv->schemes_treeview));
	model = GTK_TREE_MODEL (dlg->priv->schemes_treeview_model);

	if (gtk_tree_selection_get_selected (selection,
					     &model,
					     &iter))
	{
		gchar *id;
		gchar *name;

		gtk_tree_model_get (model, &iter,
				    ID_COLUMN, &id,
				    NAME_COLUMN, &name,
				    -1);

		if (!uninstall_style_scheme (id))
		{
			gedit_warning (GTK_WINDOW (dlg),
				       _("Could not remove color scheme \"%s\"."),
				       name);
		}
		else
		{
			const gchar *real_new_id;
			gchar *new_id = NULL;
			GtkTreePath *path;
			GtkTreeIter new_iter;
			gboolean new_iter_set = FALSE;


			path = gtk_tree_model_get_path (model, &iter);


			gtk_tree_path_next (path);
			if (!gtk_tree_model_get_iter (model, &new_iter, path))
			{


				gtk_tree_path_free (path);

				path = gtk_tree_model_get_path (model, &iter);

				gtk_tree_path_prev (path);
				if (gtk_tree_model_get_iter (model, &new_iter, path))
					new_iter_set = TRUE;
			}
			else
			{
				new_iter_set = TRUE;
			}

			gtk_tree_path_free (path);

			if (new_iter_set)
				gtk_tree_model_get (model, &new_iter,
						    ID_COLUMN, &new_id,
						    -1);

			real_new_id = populate_color_scheme_list (dlg, new_id);
			g_free (new_id);

			set_buttons_sensisitivity_according_to_scheme (dlg, real_new_id);

			if (real_new_id != NULL)
			{
				g_settings_set_string (dlg->priv->editor,
						       GEDIT_SETTINGS_SCHEME,
						       real_new_id);
			}
		}

		g_free (id);
		g_free (name);
	}
}
