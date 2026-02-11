sidebar_remove_document(GeanyDocument *doc)
{
	openfiles_remove(doc);

	if (GTK_IS_WIDGET(doc->priv->tag_tree))
	{
		gtk_widget_destroy(doc->priv->tag_tree);

		g_object_unref(doc->priv->tag_tree);
		doc->priv->tag_tree = NULL;
	}
}
