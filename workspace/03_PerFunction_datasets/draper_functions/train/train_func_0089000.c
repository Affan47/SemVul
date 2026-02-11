anjuta_docman_update_combo_label (AnjutaDocman *docman,
                                  IAnjutaDocument *doc)
{
	GtkTreeIter iter;
	GFile *file = NULL;
	gchar *filename;

	if (!anjuta_docman_get_iter_for_document (docman, doc, &iter))
		return;

	if (IANJUTA_IS_FILE (doc))
		file = ianjuta_file_get_file (IANJUTA_FILE (doc), NULL);

	filename = anjuta_docman_get_combo_filename (docman, doc, file);
	gtk_list_store_set (docman->priv->combo_model, &iter, 1, filename, -1);
	g_free (filename);
}
