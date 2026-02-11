tp_connection_block_contacts_async (TpConnection *self,
    guint n_contacts,
    TpContact * const *contacts,
    gboolean report_abusive,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  GSimpleAsyncResult *result;
  GArray *handles;
  gboolean supplied_contacts_are_valid;

  g_return_if_fail (TP_IS_CONNECTION (self));
  g_return_if_fail (n_contacts > 0);

  supplied_contacts_are_valid = _tp_contacts_to_handles (self, n_contacts,
      contacts, &handles);
  g_return_if_fail (supplied_contacts_are_valid);

  result = g_simple_async_result_new ((GObject *) self, callback, user_data,
      tp_connection_block_contacts_async);

  tp_cli_connection_interface_contact_blocking_call_block_contacts (self, -1,
      handles, report_abusive, generic_callback, result, g_object_unref, NULL);
  g_array_unref (handles);
}
