camel_folder_get_quota_info_finish (CamelFolder *folder,
                                    GAsyncResult *result,
                                    GError **error)
{
	CamelFolderClass *class;

	g_return_val_if_fail (CAMEL_IS_FOLDER (folder), NULL);

	class = CAMEL_FOLDER_GET_CLASS (folder);
	g_return_val_if_fail (class->get_quota_info_finish != NULL, NULL);

	return class->get_quota_info_finish (folder, result, error);
}
