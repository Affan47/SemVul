enum_pref_create_widget (GOConfNode *node, GtkWidget *grid,
			 gint row, GType enum_type,
			 enum_conf_setter_t setter,
			 enum_conf_getter_t getter,
			 gchar const *default_label,
                         char const *(*label_getter)(int))
{
	unsigned int	 i;
	GtkTreeIter	 iter;
	GtkCellRenderer	*renderer;
	GEnumClass	*enum_class = G_ENUM_CLASS (g_type_class_ref (enum_type));
	GtkWidget	*combo = gtk_combo_box_new ();
	GtkListStore	*model = gtk_list_store_new (2,
		G_TYPE_STRING, G_TYPE_POINTER);
	gint             current = getter ();
	gint             current_index = -1;

	for (i = 0; i < enum_class->n_values ; i++) {
		gtk_list_store_append (model, &iter);
		gtk_list_store_set (model, &iter,
			0,	label_getter ((int) enum_class->values[i].value),
			1,	enum_class->values + i,
			-1);
		if (enum_class->values[i].value == current)
			current_index = i;
	}

	g_type_class_unref (enum_class);

	gtk_combo_box_set_model (GTK_COMBO_BOX (combo), GTK_TREE_MODEL (model));
	g_object_unref (model);
	renderer = gtk_cell_renderer_text_new ();
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, TRUE);
	gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer, "text", 0, NULL);

	gtk_combo_box_set_active (GTK_COMBO_BOX (combo), current_index);

	gtk_grid_attach (GTK_GRID (grid), combo, 1, row, 1, 1);

	g_signal_connect (G_OBJECT (combo), "changed",
		G_CALLBACK (cb_enum_changed), (gpointer) setter);
	connect_notification (node, (GOConfMonitorFunc)enum_pref_conf_to_widget,
			      combo, grid);

	pref_create_label (node, grid, row, default_label, combo);
	set_tip (node, combo);
}
