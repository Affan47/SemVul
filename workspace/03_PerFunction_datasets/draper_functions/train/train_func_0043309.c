constructed (GObject *object)
{
  TpTestsContactListManager *self = TP_TESTS_CONTACT_LIST_MANAGER (object);
  void (*chain_up) (GObject *) =
      ((GObjectClass *) tp_tests_contact_list_manager_parent_class)->constructed;

  if (chain_up != NULL)
    {
      chain_up (object);
    }

  self->priv->conn = tp_base_contact_list_get_connection (
      TP_BASE_CONTACT_LIST (self), NULL);
  self->priv->status_changed_id = g_signal_connect (self->priv->conn,
      "status-changed", G_CALLBACK (status_changed_cb), self);

  self->priv->contact_repo = tp_base_connection_get_handles (self->priv->conn,
      TP_HANDLE_TYPE_CONTACT);
  self->priv->group_repo = tp_base_connection_get_handles (self->priv->conn,
      TP_HANDLE_TYPE_GROUP);
  self->priv->groups = tp_handle_set_new (self->priv->group_repo);
}
