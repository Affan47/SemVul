test_new (void)
{
  PolkitBackendLocalAuthorizationStore *store;
  gchar *data_dir_path;
  GFile *data_dir;

  data_dir_path = polkit_test_get_data_path (DATA_DIR);
  g_assert (data_dir_path);

  data_dir = g_file_new_for_path (data_dir_path);
  g_assert (data_dir);

  g_free (data_dir_path);

  store = polkit_backend_local_authorization_store_new (data_dir, DATA_EXT);
  g_assert (store);
}
