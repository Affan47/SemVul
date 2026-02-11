g_mount_source_ask_question_async (GMountSource       *source,
				   const char         *message_string,
				   const char        **choices,
				   GAsyncReadyCallback callback,
				   gpointer            user_data)
{
  GSimpleAsyncResult *result;
  GVfsDBusMountOperation *proxy;

  proxy = create_mount_operation_proxy_sync (source, callback, user_data);
  if (proxy == NULL)
    return;


  g_dbus_proxy_set_default_timeout (G_DBUS_PROXY (proxy), 1000 * 60 * 30);

  result = g_simple_async_result_new (G_OBJECT (source), callback, user_data,
                                      g_mount_source_ask_question_async);

  gvfs_dbus_mount_operation_call_ask_question (proxy,
                                               message_string ? message_string : "",
                                               choices,
                                               NULL,
                                               (GAsyncReadyCallback) ask_question_reply,
                                               result);
  g_object_unref (proxy);
}
