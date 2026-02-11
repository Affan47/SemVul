refresh_notebook (GeditDocumentsPanel *panel,
		  GeditNotebook       *notebook,
		  GtkTreeIter         *parent)
{
	GList *tabs;
	GList *l;
	GtkTreeStore *tree_store;
	GeditTab *active_tab;

	gedit_debug (DEBUG_PANEL);

	tree_store = GTK_TREE_STORE (panel->priv->model);

	active_tab = gedit_window_get_active_tab (panel->priv->window);

	tabs = gtk_container_get_children (GTK_CONTAINER (notebook));

	for (l = tabs; l != NULL; l = g_list_next (l))
	{
		GdkPixbuf *pixbuf;
		gchar *name;
		GtkTreeIter iter;

		name = tab_get_name (GEDIT_TAB (l->data));
		pixbuf = _gedit_tab_get_icon (GEDIT_TAB (l->data));


		gtk_tree_store_append (tree_store, &iter, parent);
		gtk_tree_store_set (tree_store,
				    &iter,
				    PIXBUF_COLUMN, pixbuf,
				    NAME_COLUMN, name,
				    NOTEBOOK_COLUMN, notebook,
				    TAB_COLUMN, l->data,
				    -1);

		g_free (name);
		if (pixbuf != NULL)
		{
			g_object_unref (pixbuf);
		}

		if (l->data == active_tab)
		{
			select_iter (panel, &iter);
		}
	}

	g_list_free (tabs);
}
