camel_folder_cmp_uids (CamelFolder *folder,
                       const gchar *uid1,
                       const gchar *uid2)
{
	CamelFolderClass *class;

	g_return_val_if_fail (CAMEL_IS_FOLDER (folder), 0);
	g_return_val_if_fail (uid1 != NULL, 0);
	g_return_val_if_fail (uid2 != NULL, 0);

	class = CAMEL_FOLDER_GET_CLASS (folder);
	g_return_val_if_fail (class->cmp_uids != NULL, 0);

	return class->cmp_uids (folder, uid1, uid2);
}
