prepare_simple_destination_page (GtkAssistant *assistant,
                          GtkWidget *vbox)
{
	EImportAssistantPrivate *priv;
	ImportDestinationPage *page;
	ImportSimplePage *simple_page;

	priv = E_IMPORT_ASSISTANT_GET_PRIVATE (assistant);
	page = &priv->destination_page;
	simple_page = &priv->simple_page;

	if (page->control)
		gtk_container_remove (GTK_CONTAINER (vbox), page->control);

	page->control = create_importer_control (
		priv->import, (EImportTarget *)
		simple_page->target, simple_page->importer);

	gtk_box_pack_start (GTK_BOX (vbox), page->control, TRUE, TRUE, 0);
	gtk_assistant_set_page_complete (assistant, vbox, TRUE);

	return FALSE;
}
