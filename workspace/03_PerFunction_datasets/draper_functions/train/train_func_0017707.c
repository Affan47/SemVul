import_simple_done (EImport *ei,
                    gpointer user_data)
{
	EImportAssistant *import_assistant = user_data;
	EImportAssistantPrivate *priv;

	g_return_if_fail (import_assistant != NULL);

	priv = import_assistant->priv;
	g_return_if_fail (priv != NULL);
	g_return_if_fail (priv->fileuris != NULL);
	g_return_if_fail (priv->simple_page.target != NULL);

	if (import_assistant->priv->fileuris->len > 0) {
		import_status (ei, "", 0, import_assistant);


		g_free (priv->simple_page.target->uri_src);
		priv->simple_page.target->uri_src =
			g_ptr_array_remove_index (priv->fileuris, 0);

		e_import_import (
			priv->import, priv->import_target,
			priv->import_importer, import_status,
			import_simple_done, import_assistant);
	} else
		import_done (ei, import_assistant);
}
