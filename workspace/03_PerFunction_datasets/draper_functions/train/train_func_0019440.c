load_si_combo (GtkWidget *w, G_GNUC_UNUSED GOFormatSel *gfs)
{
	GtkComboBox *c = GTK_COMBO_BOX (w);
	GtkListStore *store = GTK_LIST_STORE (gtk_combo_box_get_model (c));
	guint i;
	GtkCellRenderer  *cell;

	for (i = 0; i < G_N_ELEMENTS (si_units); i++)
		gtk_list_store_insert_with_values
			(store, NULL, i,
			 0, _(si_units[i].name),
			 1, si_units[i].unit,
			 2, si_units[i].scale,
			 -1);
	cell = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(c), cell, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(c), cell, "text",
				       0, NULL);
	gtk_combo_box_set_id_column (c, 1);
}
