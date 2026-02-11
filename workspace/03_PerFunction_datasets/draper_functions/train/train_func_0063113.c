on_notebook_page_close_button_click (GtkButton* button,
									AnjutaDocman* docman)
{
	AnjutaDocmanPage *page;

	page = anjuta_docman_get_current_page (docman);
	if (page == NULL || page->close_button != GTK_WIDGET (button))
	{

		GList* node;
		for (node = docman->priv->pages; node != NULL; node = g_list_next (node))
		{
			page = (AnjutaDocmanPage *) node->data;
			if (page->close_button == GTK_WIDGET (button))
			{
				anjuta_docman_set_current_document (docman, page->doc);
				break;
			}
		}
		if (node == NULL)
			return;
	}

	if (page != NULL)
		on_close_file_activate (NULL, docman->priv->plugin);
}
