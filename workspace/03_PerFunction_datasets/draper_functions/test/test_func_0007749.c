tp_tests_bug19101_connection_get_contact_attributes (
    TpSvcConnectionInterfaceContacts *iface,
    const GArray *handles,
    const char **interfaces,
    gboolean hold,
    DBusGMethodInvocation *context)
{
  TpBaseConnection *base_conn = TP_BASE_CONNECTION (iface);
  GHashTable *result;
  guint i;
  const gchar *assumed_interfaces[] = {
    TP_IFACE_CONNECTION,
    NULL
  };

  if (handles->len == 1 &&
      g_array_index (handles, TpHandle, 0) ==
      tp_base_connection_get_self_handle (base_conn))
    {
      DEBUG ("called for self-handle (during preparation), not being rubbish");


      result = tp_contacts_mixin_get_contact_attributes ((GObject *) iface,
          handles, interfaces, assumed_interfaces, NULL);
      goto finally;
    }

  DEBUG ("called; returning rubbish");

  result = g_hash_table_new_full (NULL, NULL, NULL,
      (GDestroyNotify) g_hash_table_unref);

  for (i = 0 ; i < handles->len ; i++)
    {
      TpHandle h= g_array_index (handles, TpHandle, i);
      GHashTable *attr_hash = g_hash_table_new_full (NULL, NULL, NULL, NULL);

      g_hash_table_insert (result, GUINT_TO_POINTER(h), attr_hash);
    }

finally:
  tp_svc_connection_interface_contacts_return_from_get_contact_attributes (
      context, result);
  g_hash_table_unref (result);
}
