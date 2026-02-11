g_vfs_ftp_task_setup_data_connection_epsv (GVfsFtpTask *task, GVfsFtpMethod method)
{
  const char *s;
  char **reply;
  guint port;
  GSocketAddress *addr;
  guint status;
  gboolean success;

  g_assert (task->error == NULL);

  status = g_vfs_ftp_task_send_and_check (task, G_VFS_FTP_PASS_500, NULL, NULL, &reply, "EPSV");
  if (G_VFS_FTP_RESPONSE_GROUP (status) != 2)
    return G_VFS_FTP_METHOD_ANY;


  s = strrchr (reply[0], '(');
  if (!s)
    goto fail;

  s += 4;
  port = strtoul (s, NULL, 10);
  if (port == 0)
    goto fail;

  g_strfreev (reply);
  addr = g_vfs_ftp_task_create_remote_address (task, port);
  if (addr == NULL)
    return G_VFS_FTP_METHOD_ANY;

  success = g_vfs_ftp_connection_open_data_connection (task->conn,
                                                       addr,
                                                       task->cancellable,
                                                       &task->error);
  g_object_unref (addr);
  return success ? G_VFS_FTP_METHOD_EPSV : G_VFS_FTP_METHOD_ANY;

fail:
  g_strfreev (reply);
  return G_VFS_FTP_METHOD_ANY;
}
