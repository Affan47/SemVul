e_mail_label_list_store_get_color (EMailLabelListStore *store,
                                   GtkTreeIter *iter,
                                   GdkColor *color)
{
	gchar *encoded;
	gchar **strv;
	gboolean valid;


	g_return_val_if_fail (E_IS_MAIL_LABEL_LIST_STORE (store), FALSE);
	g_return_val_if_fail (iter != NULL, FALSE);
	g_return_val_if_fail (color != NULL, FALSE);

	gtk_tree_model_get (GTK_TREE_MODEL (store), iter, 0, &encoded, -1);

	strv = g_strsplit_set (encoded, ":|", 3);

	if (g_strv_length (strv) >= 2)
		valid = gdk_color_parse (strv[1], color);
	else
		valid = FALSE;

	g_strfreev (strv);
	g_free (encoded);

	return valid;
}
