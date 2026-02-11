brasero_split_dialog_merge_clicked_cb (GtkButton *button,
				       BraseroSplitDialog *self)
{
	BraseroSplitDialogPrivate *priv;
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	priv = BRASERO_SPLIT_DIALOG_PRIVATE (self);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (priv->tree));
	model = gtk_tree_view_get_model (GTK_TREE_VIEW (priv->tree));
	if (!gtk_tree_model_get_iter_first (model, &iter))
		return;

	do {
		guint64 end;
		guint64 start;
		gchar *end_str;
		gchar *start_str;
		GtkTreeIter next;
		gchar *length_str;
		GtkTreeIter child;

		if (!gtk_tree_selection_iter_is_selected (selection, &iter))
			continue;

		next = iter;
		if (!gtk_tree_model_iter_next (model, &next))
			continue;

		if (!gtk_tree_selection_iter_is_selected (selection, &next))
			continue;

		gtk_tree_model_get (model, &iter,
				    START_COL, &start,
				    -1);

		gtk_tree_model_sort_convert_iter_to_child_iter (GTK_TREE_MODEL_SORT (model),
								&child,
								&iter);

		do {
			GtkTreeIter next_child;

			gtk_tree_model_get (model, &next,
					    END_COL, &end,
					   -1);

			gtk_tree_model_sort_convert_iter_to_child_iter (GTK_TREE_MODEL_SORT (model),
									&next_child,
									&next);

			if (!gtk_list_store_remove (priv->model, &next_child))
				break;

			gtk_tree_model_sort_convert_child_iter_to_iter (GTK_TREE_MODEL_SORT (model),
									&next,
									&next_child);

		} while (gtk_tree_selection_iter_is_selected (selection, &next));

		length_str = brasero_units_get_time_string (end - start, TRUE, FALSE);
		start_str = brasero_units_get_time_string (start, TRUE, FALSE);
		end_str = brasero_units_get_time_string (end, TRUE, FALSE);

		gtk_list_store_set (priv->model, &child,
				    START_COL, (gint64) start,
				    END_COL, (gint64) end,
				    LENGTH_COL, (gint64) end - start,
				    START_STR_COL, start_str,
				    END_STR_COL, end_str,
				    LENGTH_STR_COL, length_str,
				    -1);
		g_free (length_str);
		g_free (start_str);
		g_free (end_str);

		gtk_tree_model_sort_convert_child_iter_to_iter (GTK_TREE_MODEL_SORT (model),
								&iter,
								&child);

	} while (gtk_tree_model_iter_next (model, &iter));

	if (gtk_tree_model_iter_n_children (GTK_TREE_MODEL (priv->model), NULL) == 1)
		gtk_list_store_clear (priv->model);
}
