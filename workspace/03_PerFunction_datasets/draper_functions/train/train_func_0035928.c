rename_cb (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  GVfsAfpConnection *conn = G_VFS_AFP_CONNECTION (source_object);
  GSimpleAsyncResult *simple = G_SIMPLE_ASYNC_RESULT (user_data);

  GVfsAfpReply *reply;
  GError *err = NULL;
  AfpResultCode res_code;

  reply = g_vfs_afp_connection_send_command_finish (conn, res, &err);
  if (!reply)
  {
    g_simple_async_result_take_error (simple, err);
    goto done;
  }

  res_code = g_vfs_afp_reply_get_result_code (reply);
  g_object_unref (reply);

  if (res_code != AFP_RESULT_NO_ERROR)
  {
    switch (res_code)
    {
      case AFP_RESULT_ACCESS_DENIED:
        g_simple_async_result_set_error (simple, G_IO_ERROR, G_IO_ERROR_PERMISSION_DENIED,
                                         _("Permission denied"));
        break;
      case AFP_RESULT_CANT_RENAME:
        g_simple_async_result_set_error (simple, G_IO_ERROR, G_IO_ERROR_INVALID_FILENAME,
                                  _("Can't rename volume"));
        break;
      case AFP_RESULT_OBJECT_EXISTS:
        g_simple_async_result_set_error (simple, G_IO_ERROR, G_IO_ERROR_EXISTS,
                                  _("Object with that name already exists"));
        break;
      case AFP_RESULT_OBJECT_LOCKED:
        g_simple_async_result_set_error (simple, G_IO_ERROR, G_IO_ERROR_FAILED,
                                  _("Target object is marked as not renameable (RenameInhibit)"));
        break;
      case AFP_RESULT_OBJECT_NOT_FOUND:
        g_simple_async_result_set_error (simple, G_IO_ERROR, G_IO_ERROR_NOT_FOUND,
                                  _("Target object doesn't exist"));
        break;
      case AFP_RESULT_VOL_LOCKED:
        g_simple_async_result_set_error (simple, G_IO_ERROR, G_IO_ERROR_PERMISSION_DENIED,
                                  _("Volume is read-only"));
        break;
      default:
        g_simple_async_result_take_error (simple, afp_result_code_to_gerror (res_code));
        break;
    }
    goto done;
  }

done:
  g_simple_async_result_complete (simple);
  g_object_unref (simple);
}
