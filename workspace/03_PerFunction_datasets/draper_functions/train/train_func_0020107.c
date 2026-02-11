gbemol_library_is_visible (GtkTreeModel* model, GtkTreeIter *iter, GbemolLibrary* lib)
{
	gchar *str1, *list_str = NULL, *search_str = NULL;
	const gchar *str2, *str3;
	GtkTreeIter cmb_iter;
	gint column;
	gboolean result = TRUE;

	if (!gtk_combo_box_get_active_iter (GTK_COMBO_BOX (lib->priv->cmb_search), &cmb_iter))
		return TRUE;


	gtk_tree_model_get (GTK_TREE_MODEL (lib->priv->lst_column_search), &cmb_iter, 1, &column, -1);
	gtk_tree_model_get (model, iter, column, &str1, -1);


	str2 = gtk_entry_get_text (GTK_ENTRY (lib->priv->ent_search));


	if (!gbemol_cfg_get_int ("library", "case-sensitive"))
	{
		if (str1)
			list_str = g_utf8_casefold (str1, -1);
		if (str2)
			search_str = g_utf8_casefold (str2, -1);
	}
	else
	{
		list_str = str1;
		search_str = g_strdup (str2);
	}


	str2 = list_str;
	str3 = search_str;

	if (str2 && str3)
		if (!g_strrstr (list_str, search_str))
			result = FALSE;

	g_free (str1);
	g_free (search_str);

	return result;

}
