g_vfs_mount_info_query_bdmv_volume_info_finish (GFile          *directory,
                                                       GAsyncResult   *res,
                                                       gchar         **out_name,
                                                       GError        **error)
{
  GSimpleAsyncResult *simple = G_SIMPLE_ASYNC_RESULT (res);
  GIcon *ret;

  g_warn_if_fail (g_simple_async_result_get_source_tag (simple) == g_vfs_mount_info_query_bdmv_volume_info);

  ret = NULL;

  if (g_simple_async_result_propagate_error (simple, error))
    goto out;

  ret = g_simple_async_result_get_op_res_gpointer (simple);

  if (out_name != NULL)
    *out_name = g_strdup (g_object_get_data (G_OBJECT (simple), "name"));

 out:
  return ret;
}
