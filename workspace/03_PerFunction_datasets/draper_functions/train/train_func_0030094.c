glade_gtk_cell_layout_remove_child (GladeWidgetAdaptor *adaptor,
				    GObject            *container,
				    GObject            *child)
{
	GtkCellLayout *layout = GTK_CELL_LAYOUT (container);
	GList *l, *children = gtk_cell_layout_get_cells (layout);


	for (l = children; l; l = g_list_next (l))
		if (l->data != child)
			g_object_ref (l->data);
		else
			l->data = NULL;


	gtk_cell_layout_clear (layout);


	for (l = children; l; l = g_list_next (l))
	{
		if (l->data == NULL) continue;

		gtk_cell_layout_pack_start (layout,
					    GTK_CELL_RENDERER (l->data), TRUE);


		g_object_unref (l->data);
	}

	g_list_free (children);
}
