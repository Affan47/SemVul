inf_text_session_new_with_user_table(InfCommunicationManager* manager,
                                     InfTextBuffer* buffer,
                                     InfIo* io,
                                     InfUserTable* user_table,
                                     InfSessionStatus status,
                                     InfCommunicationGroup* sync_group,
                                     InfXmlConnection* sync_connection)
{


  GObject* object;

  g_return_val_if_fail(INF_COMMUNICATION_IS_MANAGER(manager), NULL);
  g_return_val_if_fail(INF_TEXT_IS_BUFFER(buffer), NULL);
  g_return_val_if_fail(INF_IS_IO(io), NULL);
  g_return_val_if_fail(INF_IS_USER_TABLE(user_table), NULL);

  g_return_val_if_fail(
    (status == INF_SESSION_RUNNING &&
     sync_group == NULL && sync_connection == NULL) ||
    (status != INF_SESSION_RUNNING &&
     INF_COMMUNICATION_IS_GROUP(sync_group) &&
     INF_IS_XML_CONNECTION(sync_connection)),
    NULL
  );

  object = g_object_new(
    INF_TEXT_TYPE_SESSION,
    "communication-manager", manager,
    "buffer", buffer,
    "user-table", user_table,
    "status", status,
    "sync-group", sync_group,
    "sync-connection", sync_connection,
    "io", io,
    NULL
  );

  return INF_TEXT_SESSION(object);
}
