camel_folder_count_by_expression (CamelFolder *folder,
                                  const gchar *expression,
                                  GCancellable *cancellable,
                                  GError **error)
{
	CamelFolderClass *class;

	g_return_val_if_fail (CAMEL_IS_FOLDER (folder), 0);

	class = CAMEL_FOLDER_GET_CLASS (folder);
	g_return_val_if_fail (class->count_by_expression != NULL, 0);


	return class->count_by_expression (folder, expression, cancellable, error);
}
