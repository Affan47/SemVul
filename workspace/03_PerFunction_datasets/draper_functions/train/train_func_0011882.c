my_get_avatar_tokens (TpSvcConnectionInterfaceAvatars *avatars,
                      const GArray *contacts,
                      DBusGMethodInvocation *context)
{
  TpTestsContactsConnection *self = TP_TESTS_CONTACTS_CONNECTION (avatars);
  TpBaseConnection *base = TP_BASE_CONNECTION (avatars);
  TpHandleRepoIface *contact_repo = tp_base_connection_get_handles (base,
      TP_HANDLE_TYPE_CONTACT);
  GError *error = NULL;
  GHashTable *result;
  guint i;

  TP_BASE_CONNECTION_ERROR_IF_NOT_CONNECTED (base, context);

  if (!tp_handles_are_valid (contact_repo, contacts, FALSE, &error))
    {
      dbus_g_method_return_error (context, error);
      g_error_free (error);
      return;
    }

  result = g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, NULL);

  for (i = 0; i < contacts->len; i++)
    {
      TpHandle handle = g_array_index (contacts, TpHandle, i);
      AvatarData *a = g_hash_table_lookup (self->priv->avatars,
          GUINT_TO_POINTER (handle));

      if (a == NULL || a->token == NULL)
        {


          a = avatar_data_new (NULL, NULL, "");
          g_hash_table_insert (self->priv->avatars,
              GUINT_TO_POINTER (handle), a);
          tp_svc_connection_interface_avatars_emit_avatar_updated (self,
              handle, a->token);
        }

      g_hash_table_insert (result, GUINT_TO_POINTER (handle),
          a->token);
    }

  tp_svc_connection_interface_avatars_return_from_get_known_avatar_tokens (
      context, result);
  g_hash_table_unref (result);
}
