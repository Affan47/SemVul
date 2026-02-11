camel_store_create_folder (CamelStore *store,
                           const gchar *parent_name,
                           const gchar *folder_name,
                           gint io_priority,
                           GCancellable *cancellable,
                           GAsyncReadyCallback callback,
                           gpointer user_data)
{
	CamelStoreClass *class;

	g_return_if_fail (CAMEL_IS_STORE (store));
	g_return_if_fail (folder_name != NULL);

	class = CAMEL_STORE_GET_CLASS (store);
	g_return_if_fail (class->create_folder != NULL);

	class->create_folder (
		store, parent_name, folder_name, io_priority,
		cancellable, callback, user_data);
}
