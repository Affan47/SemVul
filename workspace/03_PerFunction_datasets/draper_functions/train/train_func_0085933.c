populate_model (GtkTreeModel *store, GList *docs)
{
	GtkTreeIter iter;

	while (docs != NULL)
	{
		GeditDocument *doc;
		gchar *name;

		doc = GEDIT_DOCUMENT (docs->data);

		name = gedit_document_get_short_name_for_display (doc);

		gtk_list_store_append (GTK_LIST_STORE (store), &iter);
		gtk_list_store_set (GTK_LIST_STORE (store), &iter,
				    SAVE_COLUMN, TRUE,
				    NAME_COLUMN, name,
				    DOC_COLUMN, doc,
			            -1);

		g_free (name);

		docs = g_list_next (docs);
	}
}
