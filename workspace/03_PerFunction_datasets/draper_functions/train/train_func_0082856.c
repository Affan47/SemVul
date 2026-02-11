pgd_layers_create_widget (PopplerDocument *document)
{
	PgdLayersDemo    *demo;
	GtkWidget        *swindow;
	GtkWidget        *treeview;
	GtkTreeModel     *model;
	GtkCellRenderer  *renderer;
	GtkTreeSelection *selection;
	GtkWidget        *hpaned, *viewer;

	demo = g_new0 (PgdLayersDemo, 1);
	demo->doc = g_object_ref (document);

	hpaned = gtk_hpaned_new ();

	viewer = pgd_layers_create_viewer (demo);

	swindow = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),
					GTK_POLICY_AUTOMATIC,
					GTK_POLICY_AUTOMATIC);

	model = pgd_layers_create_model (document);
	treeview = gtk_tree_view_new_with_model (model);
	demo->treeview = treeview;
	g_object_unref (model);

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
						     0, "Layer",
						     renderer,
						     "markup", LAYERS_TITLE_COLUMN,
						     NULL);
	g_object_set (G_OBJECT (renderer), "ellipsize", PANGO_ELLIPSIZE_END, NULL);
	g_object_set (G_OBJECT (gtk_tree_view_get_column (GTK_TREE_VIEW (treeview), 0)),
		      "expand", TRUE, NULL);

	if (GTK_IS_TREE_STORE (model)) {
		renderer = gtk_cell_renderer_toggle_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
							     1, "Show/Hide",
							     renderer,
							     "active", LAYERS_VISIBILITY_COLUMN,
							     "activatable", LAYERS_ENABLE_COLUMN,
							     "visible", LAYERS_SHOWTOGGLE_COLUMN,
							     NULL);

		g_signal_connect (renderer, "toggled",
				  G_CALLBACK (pgd_layers_visibility_changed),
				  (gpointer)demo);
		gtk_tree_view_column_set_clickable (gtk_tree_view_get_column (GTK_TREE_VIEW (treeview), 1),
						    TRUE);
	}

	gtk_tree_selection_set_mode (gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview)),
				     GTK_SELECTION_NONE);

	gtk_container_add (GTK_CONTAINER (swindow), treeview);
	gtk_widget_show (treeview);

	gtk_paned_add1 (GTK_PANED (hpaned), swindow);
	gtk_widget_show (swindow);

	gtk_paned_add2 (GTK_PANED (hpaned), viewer);
	gtk_widget_show (viewer);

	gtk_paned_set_position (GTK_PANED (hpaned), 150);

	g_object_weak_ref (G_OBJECT (hpaned),
			   (GWeakNotify)pgd_layers_free,
			   (gpointer)demo);

	return hpaned;
}
