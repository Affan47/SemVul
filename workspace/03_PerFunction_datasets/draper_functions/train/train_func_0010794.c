import_intelligent_done (EImport *ei,
                         gpointer user_data)
{
	EImportAssistant *import_assistant = user_data;
	ImportSelectionPage *page;

	page = &import_assistant->priv->selection_page;

	if (page->current && (page->current = page->current->next)) {
		import_status (ei, "", 0, import_assistant);
		import_assistant->priv->import_importer = page->current->data;
		e_import_import (
			import_assistant->priv->import,
			(EImportTarget *) page->target,
			import_assistant->priv->import_importer,
			import_status, import_intelligent_done,
			import_assistant);
	} else
		import_done (ei, import_assistant);
}
