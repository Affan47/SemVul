update_document_ui (AnjutaPlugin *plugin, IAnjutaDocument *doc)
{
	if (doc == NULL)
	{
		update_document_ui_disable_all (plugin);
		return;
	}
	update_document_ui_enable_all (plugin);
	update_document_ui_save_items (plugin, doc);
	update_document_ui_interface_items (plugin, doc);
}
