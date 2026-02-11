update_tag_list (GthTestCategory *test)
{
	char **tags;
	int    i;

	gtk_list_store_clear (GTK_LIST_STORE (test->priv->tag_store));

	tags = g_strdupv (gth_tags_file_get_tags (gth_main_get_default_tag_file ()));
	for (i = 0; tags[i] != NULL; i++) {
		GtkTreeIter iter;

		gtk_list_store_append (GTK_LIST_STORE (test->priv->tag_store), &iter);
		gtk_list_store_set (GTK_LIST_STORE (test->priv->tag_store), &iter,
				    0, tags[i],
				    -1);
	}

	g_strfreev (tags);
}
