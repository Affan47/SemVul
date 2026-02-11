pl_cell_data_function(GtkTreeViewColumn *col,
                                  GtkCellRenderer   *renderer,
                                  GtkTreeModel      *model,
                                  GtkTreeIter       *iter,
                                  gpointer           userdata)
{
	GMedialib *gml = GMEDIALIB(userdata);
	guint      pos = 0;
	guint      cur_pos = (guint)gml->playlist.current_pos;

	gtk_tree_model_get(model, iter, 0, &pos, -1);

	if (pos == cur_pos)
		g_object_set(renderer, "weight", PANGO_WEIGHT_BOLD,
		             "weight-set", TRUE, NULL);
	else
		g_object_set(renderer, "weight-set", FALSE, NULL);
}
