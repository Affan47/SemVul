imapx_folder_finalize (GObject *object)
{
	CamelIMAPXFolder *folder = CAMEL_IMAPX_FOLDER (object);

	if (folder->ignore_recent != NULL)
		g_hash_table_unref (folder->ignore_recent);

	g_mutex_clear (&folder->search_lock);
	g_mutex_clear (&folder->stream_lock);

	g_mutex_clear (&folder->priv->property_lock);
	g_strfreev (folder->priv->quota_root_names);

	g_mutex_clear (&folder->priv->move_to_hash_table_lock);
	g_hash_table_destroy (folder->priv->move_to_real_junk_uids);
	g_hash_table_destroy (folder->priv->move_to_real_trash_uids);


	G_OBJECT_CLASS (camel_imapx_folder_parent_class)->finalize (object);
}
