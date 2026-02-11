rev_list_view_query_tooltip (GtkWidget  *widget,
                             gint        x,
                             gint        y,
                             gboolean    keyboard_mode,
                             GtkTooltip *tooltip)
{
	GiggleRevListViewPriv *priv = GET_PRIV (widget);
	int                    bin_x, bin_y;
	GiggleRevision        *revision = NULL;
	GtkTreePath           *path = NULL;
	GtkTreeViewColumn     *column;
	GtkTreeIter            iter;
	GtkTreeModel          *model;
	GdkRectangle           cell_area;
	GString               *markup;
	GList                 *revs;

	gtk_tree_view_convert_widget_to_bin_window_coords
		(GTK_TREE_VIEW (widget), x, y, &bin_x, &bin_y);

	if (!gtk_tree_view_get_path_at_pos
			(GTK_TREE_VIEW (widget), bin_x, bin_y,
			 &path, &column, NULL, NULL))
		goto finish;

	if (column != priv->emblem_column)
		goto finish;

	model = gtk_tree_view_get_model (GTK_TREE_VIEW (widget));

	if (gtk_tree_model_get_iter (model, &iter, path))
		gtk_tree_model_get (model, &iter, COL_OBJECT, &revision, -1);

	if (!revision)
		goto finish;

	markup = g_string_new (NULL);

	revs = giggle_revision_get_branch_heads (revision);
	revision_tooltip_add_refs (markup, _("Branch"), revs);

	revs = giggle_revision_get_tags (revision);
	revision_tooltip_add_refs (markup, _("Tag"), revs);

	revs = giggle_revision_get_remotes (revision);
	revision_tooltip_add_refs (markup, _("Remote"), revs);

	if (markup->len > 0) {
		gtk_tree_view_get_cell_area (GTK_TREE_VIEW (widget), path, column, &cell_area);

		gtk_tree_view_convert_bin_window_to_widget_coords
			(GTK_TREE_VIEW (widget), cell_area.x, cell_area.y,
			 &cell_area.x, &cell_area.y);

		gtk_tooltip_set_tip_area (tooltip, &cell_area);
		gtk_tooltip_set_markup (tooltip, markup->str);
	} else {
		g_object_unref (revision);
		revision = NULL;
	}

	g_string_free (markup, TRUE);

finish:
	gtk_tree_path_free (path);

	if (revision) {
		g_object_unref (revision);
		return TRUE;
	}

	return GTK_WIDGET_CLASS (giggle_rev_list_view_parent_class)->
		query_tooltip (widget, x, y, keyboard_mode, tooltip);
}
