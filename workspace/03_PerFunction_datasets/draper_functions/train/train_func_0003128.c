simple_filetype_changed_cb (GtkComboBox *combo_box,
                            GtkAssistant *assistant)
{
	EImportAssistantPrivate *priv;
	ImportSimplePage *page;
	GtkTreeModel *model;
	GtkTreeIter iter;
	GtkWidget *vbox;
	GtkWidget *control;

	priv = E_IMPORT_ASSISTANT_GET_PRIVATE (assistant);
	page = &priv->simple_page;

	g_return_if_fail (gtk_combo_box_get_active_iter (combo_box, &iter));

	model = gtk_combo_box_get_model (combo_box);
	gtk_tree_model_get (model, &iter, 2, &page->importer, -1);

	vbox = g_object_get_data (G_OBJECT (combo_box), "page-vbox");
	g_return_if_fail (vbox != NULL);

	if (page->control)
		gtk_widget_destroy (page->control);
	page->has_preview = FALSE;

	control = e_import_get_preview_widget (
		priv->import, (EImportTarget *)
		page->target, page->importer);
	if (control) {
		page->has_preview = TRUE;
		gtk_widget_set_size_request (control, 440, 360);
	} else
		control = create_importer_control (
			priv->import, (EImportTarget *)
			page->target, page->importer);

	page->control = gtk_alignment_new (0.0, 0.0, 1.0, 1.0);
	gtk_widget_show (page->control);
	gtk_container_add (GTK_CONTAINER (page->control), control);

	gtk_box_pack_start (GTK_BOX (vbox), page->control, TRUE, TRUE, 0);
	gtk_assistant_set_page_complete (assistant, vbox, TRUE);
}
