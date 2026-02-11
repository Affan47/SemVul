gog_series_element_populate_editor (GogObject *gobj,
				    GOEditor *editor,
			   GogDataAllocator *dalloc,
			   GOCmdContext *cc)
{
	static guint series_element_pref_page = 1;
	GtkWidget *w, *gse_grid = NULL, *grid;
	GogSeriesElementClass *klass = GOG_SERIES_ELEMENT_GET_CLASS (gobj);

	if (klass->gse_populate_editor)
		gse_grid = (*klass->gse_populate_editor) (gobj, editor, cc);

	(GOG_OBJECT_CLASS(gse_parent_klass)->populate_editor) (gobj, editor, dalloc, cc);

	if (gse_grid == NULL) {
		grid = gtk_grid_new ();
		gtk_grid_set_row_spacing (GTK_GRID (grid), 6);
		gtk_grid_set_column_spacing (GTK_GRID (grid), 12);
		gtk_container_set_border_width (GTK_CONTAINER (grid), 12);
	} else {
		grid = gse_grid;
		gtk_grid_insert_row (GTK_GRID (grid), 0);
	}
	w = gtk_label_new (_("Index:"));
	g_object_set (G_OBJECT (w), "xalign", 0., NULL);
	gtk_grid_attach (GTK_GRID (grid), w, 0, 0, 1, 1);
	w = gtk_spin_button_new_with_range (0, G_MAXINT, 1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (w),
				   GOG_SERIES_ELEMENT(gobj)->index);
	g_signal_connect (G_OBJECT (w),
			  "value_changed",
			  G_CALLBACK (cb_index_changed), gobj);
	gtk_grid_attach (GTK_GRID (grid), w, 1, 0, 1, 1);
	gtk_widget_show_all (grid);

	if (gse_grid == NULL)
		go_editor_add_page (editor, grid, _("Settings"));

	go_editor_set_store_page (editor, &series_element_pref_page);
}
