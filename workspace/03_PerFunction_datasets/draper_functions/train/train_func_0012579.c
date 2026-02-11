prepare_contact_list_props_cb (TpProxy *proxy,
    GHashTable *properties,
    const GError *error,
    gpointer user_data,
    GObject *weak_object)
{
  TpConnection *self = (TpConnection *) proxy;
  GSimpleAsyncResult *result = user_data;
  gboolean valid;

  self->priv->contact_list_properties_fetched = TRUE;

  if (error != NULL)
    {
      DEBUG ("Error preparing ContactList properties: %s", error->message);
      g_simple_async_result_set_from_error (result, error);
      goto OUT;
    }

  self->priv->contact_list_state = tp_asv_get_uint32 (properties,
      "ContactListState", &valid);
  if (!valid)
    {
      DEBUG ("Connection %s doesn't have ContactListState property",
          tp_proxy_get_object_path (self));
    }

  self->priv->contact_list_persists = tp_asv_get_boolean (properties,
      "ContactListPersists", &valid);
  if (!valid)
    {
      DEBUG ("Connection %s doesn't have ContactListPersists property",
          tp_proxy_get_object_path (self));
    }

  self->priv->can_change_contact_list = tp_asv_get_boolean (properties,
      "CanChangeContactList", &valid);
  if (!valid)
    {
      DEBUG ("Connection %s doesn't have CanChangeContactList property",
          tp_proxy_get_object_path (self));
    }

  self->priv->request_uses_message = tp_asv_get_boolean (properties,
      "RequestUsesMessage", &valid);
  if (!valid)
    {
      DEBUG ("Connection %s doesn't have RequestUsesMessage property",
          tp_proxy_get_object_path (self));
    }

  DEBUG ("Got contact list properties; state=%d",
      self->priv->contact_list_state);

OUT:
  g_simple_async_result_complete_in_idle (result);
}
