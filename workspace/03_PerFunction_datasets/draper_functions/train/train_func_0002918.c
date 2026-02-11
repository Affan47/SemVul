move_selection (GeditHighlightModeDialog *dlg,
                gint                      howmany)
{
	GtkTreeIter iter;
	GtkTreePath *path;
	gint *indices;
	gint ret = FALSE;

	if (!gtk_tree_selection_get_selected (dlg->priv->treeview_selection, NULL, &iter) &&
	    !gtk_tree_model_get_iter_first (GTK_TREE_MODEL (dlg->priv->treemodelfilter), &iter))
	{
		return FALSE;
	}

	path = gtk_tree_model_get_path (GTK_TREE_MODEL (dlg->priv->treemodelfilter), &iter);
	indices = gtk_tree_path_get_indices (path);

	if (indices)
	{
		gint num;
		gint idx;
		GtkTreePath *new_path;

		idx = indices[0];
		num = gtk_tree_model_iter_n_children (GTK_TREE_MODEL (dlg->priv->treemodelfilter), NULL);

		if ((idx + howmany) < 0)
		{
			idx = 0;
		}
		else if ((idx + howmany) >= num)
		{
			idx = num - 1;
		}
		else
		{
			idx = idx + howmany;
		}

		new_path = gtk_tree_path_new_from_indices (idx, -1);
		gtk_tree_selection_select_path (dlg->priv->treeview_selection, new_path);
		gtk_tree_view_scroll_to_cell (GTK_TREE_VIEW (dlg->priv->treeview),
		                              new_path, NULL, TRUE, 0.5, 0);
		gtk_tree_path_free (new_path);

		ret = TRUE;
	}

	gtk_tree_path_free (path);

	return ret;
}
