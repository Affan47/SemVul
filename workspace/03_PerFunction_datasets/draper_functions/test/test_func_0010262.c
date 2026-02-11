repbalance_date_cell_data_function (GtkTreeViewColumn *col, GtkCellRenderer *renderer, GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data)
{
gchar *datestr;
gboolean is_balance;
gchar *color;
gint weight;

	gtk_tree_model_get(model, iter,
		LST_OVER_DATESTR, &datestr,
		LST_OVER_OVER, &is_balance,
		-1);

	color = NULL;
	weight = PANGO_WEIGHT_NORMAL;

	if(is_balance==TRUE)
	{
		if(PREFS->custom_colors == TRUE)
			color = PREFS->color_warn;

		weight = PANGO_WEIGHT_BOLD;
	}

	g_object_set(renderer,
		"weight", weight,
		"foreground",  color,
		"text", datestr,
		NULL);
}
