update_fetch (GitgRepositoryDialog *dialog)
{
	GtkTreeSelection *selection = gtk_tree_view_get_selection (dialog->priv->tree_view_remotes);
	GList *rows;
	GtkTreeModel *model;

	rows = gtk_tree_selection_get_selected_rows (selection, &model);

	GList *item;
	gboolean show_fetch = FALSE;

	for (item = rows; item; item = g_list_next (item))
	{
		GtkTreePath *path = (GtkTreePath *)item->data;
		GtkTreeIter iter;

		gtk_tree_model_get_iter (model, &iter, path);

		gboolean fetch;
		gtk_tree_model_get (model, &iter, COLUMN_FETCH, &fetch, -1);

		if (!fetch)
		{
			show_fetch = TRUE;
		}
	}

	if (!rows)
	{
		show_fetch = TRUE;
	}

	if (show_fetch)
	{
		gtk_image_set_from_stock (dialog->priv->image_fetch_remote, GTK_STOCK_REFRESH, GTK_ICON_SIZE_BUTTON);
		gtk_button_set_label (dialog->priv->button_fetch_remote, _("Fetch"));
	}
	else
	{
		gtk_image_set_from_stock (dialog->priv->image_fetch_remote, GTK_STOCK_CANCEL, GTK_ICON_SIZE_BUTTON);
		gtk_button_set_label (dialog->priv->button_fetch_remote, _("Cancel"));
	}

	dialog->priv->show_fetch = show_fetch;

	g_list_free_full (rows, (GDestroyNotify)gtk_tree_path_free);
}
