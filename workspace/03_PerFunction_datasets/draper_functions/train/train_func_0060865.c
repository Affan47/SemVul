draw (GtkWidget *widget, cairo_t *cr)
{
	GtkTreeModel *view_model;
	GtkTreeModel *model = NULL;
	GtkTreeView *tree_view;
	gint event_handled = FALSE;

	if (GTK_WIDGET_CLASS (gbf_project_view_parent_class)->draw != NULL)
		GTK_WIDGET_CLASS (gbf_project_view_parent_class)->draw (widget, cr);

	tree_view = GTK_TREE_VIEW (widget);
	view_model = gtk_tree_view_get_model (tree_view);
	if (GTK_IS_TREE_MODEL_FILTER (view_model))
	{
		model = gtk_tree_model_filter_get_model (GTK_TREE_MODEL_FILTER (view_model));
	}
	if (gtk_cairo_should_draw_window (cr, gtk_tree_view_get_bin_window (tree_view)) &&
	    model && GBF_IS_PROJECT_MODEL (model)) {
		GtkTreePath *root;
		GdkRectangle rect;


		root = gbf_project_model_get_project_root (GBF_PROJECT_MODEL (model));
		if (root) {
			if (view_model != model)
			{

				GtkTreePath *child_path;

				child_path = gtk_tree_model_filter_convert_child_path_to_path (GTK_TREE_MODEL_FILTER (view_model), root);
				gtk_tree_path_free (root);
				root = child_path;
			}
			gtk_tree_view_get_background_area (
				tree_view, root, gtk_tree_view_get_column (tree_view, 0), &rect);
			gtk_render_line (gtk_widget_get_style_context (widget),
			                 cr,
			                 rect.x, rect.y,
			                 rect.x + rect.width, rect.y);
			gtk_tree_path_free (root);
		}
	}

	return event_handled;
}
