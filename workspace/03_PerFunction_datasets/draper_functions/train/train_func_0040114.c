gnome_scan_paper_size_widget_build (GnomeScanParamWidget *gspw)
{
	GnomeScanPaperSizeWidgetPrivate *priv = GET_PRIVATE (gspw);
	GtkWidget *box;
	GtkCellRenderer *renderer;
	GtkTreeIter iter;
	GtkPaperSize *ps;
	GSList *node;
	gint i;

	gspw->shows_label = TRUE;
	gspw->shows_unit = TRUE;


	priv->paper_names = gtk_list_store_new (N_COLUMNS,
											G_TYPE_STRING,
											GTK_TYPE_PAPER_SIZE);

	node = GS_PARAM_SPEC_PAPER_SIZE (gspw->pspec)->enumeration;
	for (; node; node = node->next) {
		ps = node->data;
		gtk_list_store_append (priv->paper_names, &iter);
		gtk_list_store_set (priv->paper_names, &iter,
							COL_DISPLAY_NAME, gtk_paper_size_get_display_name(ps),
							COL_PS, ps,
							-1);
	}


	priv->combo = gtk_combo_box_new_with_model (GTK_TREE_MODEL (priv->paper_names));

	renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (priv->combo), renderer, TRUE);
	gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (priv->combo), renderer,
								   "text", COL_DISPLAY_NAME);


	priv->label = gtk_label_new (NULL);

	box = gtk_vbox_new (FALSE, 4);
	gtk_box_pack_start (GTK_BOX (box), priv->combo, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box), priv->label, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (gspw), box, FALSE, FALSE, 0);


	g_signal_connect (GET_PRIVATE (gspw)->combo, "changed",
					  (GCallback) gspsw_selected,
					  GNOME_SCAN_PAPER_SIZE_WIDGET (gspw));
}
