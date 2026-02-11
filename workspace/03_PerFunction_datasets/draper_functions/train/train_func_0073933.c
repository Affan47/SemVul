anjuta_docman_get_iter_for_document (AnjutaDocman *docman,
                                     IAnjutaDocument *doc,
                                     GtkTreeIter *iter)
{
	if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (docman->priv->combo_model), iter))
	{
		do
		{
			IAnjutaDocument *document;
			gboolean equal;

			gtk_tree_model_get (GTK_TREE_MODEL (docman->priv->combo_model), iter, 0, &document, -1);
			equal = (document == doc);
			g_object_unref (document);

			if (equal)
				return TRUE;
		}
		while (gtk_tree_model_iter_next (GTK_TREE_MODEL (docman->priv->combo_model), iter));
	}

	return FALSE;
}
