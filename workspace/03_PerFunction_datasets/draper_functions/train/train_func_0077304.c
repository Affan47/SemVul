get_volumes_cb (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  GVfsAfpServer *server = G_VFS_AFP_SERVER (source_object);
  GSimpleAsyncResult *simple = user_data;

  GVfsBackendAfpBrowse *afp_backend;
  GPtrArray *volumes;
  GError *err = NULL;

  afp_backend = G_VFS_BACKEND_AFP_BROWSE (g_async_result_get_source_object (G_ASYNC_RESULT (simple)));

  volumes = g_vfs_afp_server_get_volumes_finish (server, res, &err);
  if (!volumes)
  {
    g_simple_async_result_take_error (simple, err);
    goto done;
  }

  if (afp_backend->volumes)
    g_ptr_array_unref (afp_backend->volumes);
  afp_backend->volumes = volumes;

done:
  g_simple_async_result_complete (simple);
  g_object_unref (simple);
}
