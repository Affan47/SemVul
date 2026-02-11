camel_folder_get_filename (CamelFolder *folder,
                           const gchar *uid,
                           GError **error)
{
	CamelFolderClass *class;
	gchar *filename;

	g_return_val_if_fail (CAMEL_IS_FOLDER (folder), NULL);
	g_return_val_if_fail (uid != NULL, NULL);

	class = CAMEL_FOLDER_GET_CLASS (folder);
	g_return_val_if_fail (class->get_filename != NULL, NULL);

	filename = class->get_filename (folder, uid, error);
	CAMEL_CHECK_GERROR (folder, get_filename, filename != NULL, error);

	return filename;
}
