camel_vee_subfolder_data_new (CamelFolder *folder)
{
	CamelVeeSubfolderData *data;
	gchar buffer[8], *folder_id;

	g_return_val_if_fail (CAMEL_IS_FOLDER (folder), NULL);

	data = g_object_new (CAMEL_TYPE_VEE_SUBFOLDER_DATA, NULL);
	data->priv->folder = g_object_ref (folder);

	vee_subfolder_data_hash_folder (folder, buffer);
	folder_id = g_strndup (buffer, 8);

	data->priv->folder_id = camel_pstring_add (folder_id, TRUE);

	return data;
}
