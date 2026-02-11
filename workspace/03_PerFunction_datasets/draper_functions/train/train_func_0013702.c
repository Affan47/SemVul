e_mail_label_list_store_get_stock_id (EMailLabelListStore *store,
                                      GtkTreeIter *iter)
{
	gchar *encoded;
	gchar *result;
	gchar **strv;


	g_return_val_if_fail (E_IS_MAIL_LABEL_LIST_STORE (store), NULL);
	g_return_val_if_fail (iter != NULL, NULL);
	gtk_tree_model_get (GTK_TREE_MODEL (store), iter, 0, &encoded, -1);

	strv = g_strsplit_set (encoded, ":|", 3);

	if (g_strv_length (strv) >= 2)
		result = mail_label_list_store_get_stock_id (store, strv[1]);
	else
		result = NULL;

	g_strfreev (strv);
	g_free (encoded);

	return result;
}
