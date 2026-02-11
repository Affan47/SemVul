get_vol_parms_cb (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  GVfsAfpConnection *connection = G_VFS_AFP_CONNECTION (source_object);
  GSimpleAsyncResult *simple = G_SIMPLE_ASYNC_RESULT (user_data);

  GVfsAfpVolume *volume = G_VFS_AFP_VOLUME (g_async_result_get_source_object (G_ASYNC_RESULT (simple)));
  GVfsAfpVolumePrivate *priv = volume->priv;

  GVfsAfpReply *reply;
  GError *err = NULL;
  AfpResultCode res_code;

  guint16 vol_bitmap;
  GFileInfo *info;

  guint64 bytes_free, bytes_total;

  reply = g_vfs_afp_connection_send_command_finish (connection, res, &err);
  if (!reply)
  {
    g_simple_async_result_take_error (simple, err);
    goto done;
  }

  res_code = g_vfs_afp_reply_get_result_code (reply);
  if (res_code != AFP_RESULT_NO_ERROR)
  {
    g_object_unref (reply);

    g_simple_async_result_take_error (simple, afp_result_code_to_gerror (res_code));
    goto done;
  }

  g_vfs_afp_reply_read_uint16 (reply, &vol_bitmap);

  info = g_file_info_new ();

  if (vol_bitmap & AFP_VOLUME_BITMAP_ATTRIBUTE_BIT)
  {
    guint16 vol_attrs_bitmap;

    g_vfs_afp_reply_read_uint16 (reply, &vol_attrs_bitmap);

    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_FILESYSTEM_READONLY,
                                       vol_attrs_bitmap & AFP_VOLUME_ATTRIBUTES_BITMAP_READ_ONLY);
  }

  if (vol_bitmap & AFP_VOLUME_BITMAP_CREATE_DATE_BIT)
  {
    gint32 create_date;
    gint64 create_date_local;

    g_vfs_afp_reply_read_int32 (reply, &create_date);

    create_date_local = g_vfs_afp_server_time_to_local_time (priv->server, create_date);
    g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_CREATED,
                                      create_date_local);
  }

  if (vol_bitmap & AFP_VOLUME_BITMAP_MOD_DATE_BIT)
  {
    gint32 mod_date;
    gint64 mod_date_local;

    g_vfs_afp_reply_read_int32 (reply, &mod_date);

    mod_date_local = g_vfs_afp_server_time_to_local_time (priv->server, mod_date);
    g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_MODIFIED,
                                      mod_date_local);
  }

  if (vol_bitmap & AFP_VOLUME_BITMAP_EXT_BYTES_FREE_BIT)
  {
    g_vfs_afp_reply_read_uint64 (reply, &bytes_free);
    g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_FILESYSTEM_FREE,
                                      bytes_free);
  }

  if (vol_bitmap & AFP_VOLUME_BITMAP_EXT_BYTES_TOTAL_BIT)
  {
    g_vfs_afp_reply_read_uint64 (reply, &bytes_total);
    g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_FILESYSTEM_SIZE,
                                      bytes_total);
  }

  if (vol_bitmap & AFP_VOLUME_BITMAP_EXT_BYTES_FREE_BIT &&
      vol_bitmap & AFP_VOLUME_BITMAP_EXT_BYTES_TOTAL_BIT)
    g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_FILESYSTEM_USED,
                                      bytes_total - bytes_free);

  g_object_unref (reply);

  g_simple_async_result_set_op_res_gpointer (simple, info, g_object_unref);

done:
  g_simple_async_result_complete (simple);
  g_object_unref (simple);
}
