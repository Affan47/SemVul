tp_base_contact_list_fill_blocking_contact_attributes (GObject *obj,
  const GArray *contacts,
  GHashTable *attributes_hash)
{
  TpBaseContactList *self = _tp_base_connection_find_channel_manager (
      (TpBaseConnection *) obj, TP_TYPE_BASE_CONTACT_LIST);
  guint i;
  TpHandleSet *blocked;

  g_return_if_fail (TP_IS_BASE_CONTACT_LIST (self));
  g_return_if_fail (TP_IS_BLOCKABLE_CONTACT_LIST (self));
  g_return_if_fail (self->priv->conn != NULL);


  if (self->priv->state != TP_CONTACT_LIST_STATE_SUCCESS)
    return;

  blocked = tp_base_contact_list_dup_blocked_contacts (self);

  for (i = 0; i < contacts->len; i++)
    {
      TpHandle handle;
      gboolean is_blocked;

      handle = g_array_index (contacts, TpHandle, i);

      is_blocked = tp_handle_set_is_member (blocked, handle);

      tp_contacts_mixin_set_contact_attribute (attributes_hash,
          handle, TP_TOKEN_CONNECTION_INTERFACE_CONTACT_BLOCKING_BLOCKED,
          tp_g_value_slice_new_boolean (is_blocked));
    }

  tp_handle_set_destroy (blocked);
}
