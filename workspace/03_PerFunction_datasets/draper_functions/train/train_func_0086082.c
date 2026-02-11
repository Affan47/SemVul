gedit_document_is_untouched (GeditDocument *doc)
{
	g_return_val_if_fail (GEDIT_IS_DOCUMENT (doc), TRUE);

	return (doc->priv->location == NULL) &&
		(!gtk_text_buffer_get_modified (GTK_TEXT_BUFFER (doc)));
}
