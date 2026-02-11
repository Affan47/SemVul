go_gtk_grid_remove_row (GtkGrid *grid, int row)
{
	GtkContainer *cont = GTK_CONTAINER (grid);
	GList *children =
		g_list_sort (get_grid_data (grid), (GCompareFunc)by_row);
	GList *p;

	for (p = children; p; p = p->next) {
		struct go_gtk_grid_data *data = p->data;

		if (data->top_attach <= row &&
		    data->top_attach + data->height > row)
			data->height--;

		if (data->top_attach > row)
			data->top_attach--;

		if (data->height <= 0)
			gtk_container_remove (cont, data->child);
		else
			gtk_container_child_set (cont, data->child,
						 "height", data->height,
						 "top-attach", data->top_attach,
						 NULL);
	}
	g_list_free_full (children, (GDestroyNotify)g_free);
}
