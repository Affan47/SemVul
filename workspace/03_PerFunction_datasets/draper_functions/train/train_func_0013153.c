pretend_connected (gpointer data)
{
  TpTestsSimpleConnection *self = TP_TESTS_SIMPLE_CONNECTION (data);
  TpBaseConnection *conn = (TpBaseConnection *) self;
  TpHandleRepoIface *contact_repo = tp_base_connection_get_handles (conn,
      TP_HANDLE_TYPE_CONTACT);
  TpHandle self_handle;

  self_handle = tp_handle_ensure (contact_repo, self->priv->account,
      NULL, NULL);
  tp_base_connection_set_self_handle (conn, self_handle);

  if (tp_base_connection_get_status (conn) == TP_CONNECTION_STATUS_CONNECTING)
    {
      tp_base_connection_change_status (conn, TP_CONNECTION_STATUS_CONNECTED,
          TP_CONNECTION_STATUS_REASON_REQUESTED);
    }

  self->priv->connect_source = 0;
  return FALSE;
}
