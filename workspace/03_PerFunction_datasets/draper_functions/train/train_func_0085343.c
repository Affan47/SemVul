setup_combo (GtkWidget            *combo_box,
	     ComboItem            *items,
	     int                   nb_items,
	     const char           *for_type)
{
	GtkListStore          *model;
	GtkTreeIter            iter;
	GtkCellRenderer       *renderer;
	int                    i;

	model = gtk_list_store_new (NUMBER_COLUMNS,
				    G_TYPE_STRING,
				    G_TYPE_INT);

	gtk_combo_box_set_model (GTK_COMBO_BOX (combo_box),
				 GTK_TREE_MODEL (model));

	for (i = 0; i < nb_items; i++) {
		if (for_type && strcmp (for_type, items [i].show_for))
			continue;

		gtk_list_store_append (model, &iter);
		gtk_list_store_set (model, &iter,
				    COLUMN_TEXT, _(items [i].name),
				    COLUMN_TYPE, items [i].type,
				    -1);
	}

	renderer = gtk_cell_renderer_text_new ();
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo_box),
				    renderer, TRUE);
	gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo_box),
					renderer, "text", COLUMN_TEXT, NULL);

	gtk_combo_box_set_active (GTK_COMBO_BOX (combo_box), 0);
}
