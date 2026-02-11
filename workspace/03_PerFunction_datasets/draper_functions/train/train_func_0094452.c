tp_simple_client_factory_upgrade_contacts_async (
    TpSimpleClientFactory *self,
    TpConnection *connection,
    guint n_contacts,
    TpContact * const *contacts,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  GSimpleAsyncResult *result;
  GArray *features;


  g_warn_if_fail (tp_proxy_get_factory (connection) == self);

  result = g_simple_async_result_new ((GObject *) self, callback, user_data,
      tp_simple_client_factory_upgrade_contacts_async);

  features = tp_simple_client_factory_dup_contact_features (self, connection);
  tp_connection_upgrade_contacts_async (connection, n_contacts, contacts,
      features->len, (TpContactFeature *) features->data,
      upgrade_contacts_cb, result);
  g_array_unref (features);
}
