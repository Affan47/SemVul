filter_set_func(GtkTreeViewColumn *tree_column, GtkCellRenderer *cell,
			    GtkTreeModel *tree_model, GtkTreeIter *iter, gpointer data)
{
	FilterEntry *fe;

	gtk_tree_model_get(tree_model, iter, 0, &fe, -1);

	switch (GPOINTER_TO_INT(data))
		{
		case FE_ENABLE:
			g_object_set(GTK_CELL_RENDERER(cell),
				     "active", fe->enabled, NULL);
			break;
		case FE_EXTENSION:
			g_object_set(GTK_CELL_RENDERER(cell),
				     "text", fe->extensions, NULL);
			break;
		case FE_DESCRIPTION:
			g_object_set(GTK_CELL_RENDERER(cell),
				     "text", fe->description, NULL);
			break;
		case FE_CLASS:
			g_object_set(GTK_CELL_RENDERER(cell),
				     "text", _(format_class_list[fe->file_class]), NULL);
			break;
		case FE_WRITABLE:
			g_object_set(GTK_CELL_RENDERER(cell),
				     "active", fe->writable, NULL);
			break;
		case FE_ALLOW_SIDECAR:
			g_object_set(GTK_CELL_RENDERER(cell),
				     "active", fe->allow_sidecar, NULL);
			break;
		}
}
