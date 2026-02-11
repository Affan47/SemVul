init_shown_in_menu_tree_model (GeditEncodingsDialog *dialog)
{
	GtkTreeIter iter;
	gchar **enc_strv;
	GSList *list, *tmp;


	enc_strv = g_settings_get_strv (dialog->priv->enc_settings,
					GEDIT_SETTINGS_ENCODING_SHOWN_IN_MENU);

	list = _gedit_encoding_strv_to_list ((const gchar * const *)enc_strv);

	for (tmp = list; tmp != NULL; tmp = g_slist_next (tmp))
	{
		const GeditEncoding *enc;

		enc = (const GeditEncoding *) tmp->data;

		dialog->priv->show_in_menu_list = g_slist_prepend (dialog->priv->show_in_menu_list,
								   tmp->data);

		gtk_list_store_append (dialog->priv->displayed_liststore,
				       &iter);
		gtk_list_store_set (dialog->priv->displayed_liststore,
				    &iter,
				    COLUMN_CHARSET,
				    gedit_encoding_get_charset (enc),
				    COLUMN_NAME,
				    gedit_encoding_get_name (enc), -1);
	}

	g_slist_free (list);
}
