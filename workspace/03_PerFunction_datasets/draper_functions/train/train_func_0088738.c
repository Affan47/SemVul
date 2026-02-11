find_object_with_principal (GoaIdentityService *self,
                            const char         *principal,
                            gboolean            must_be_enabled)
{
  GList      *objects;
  GList      *node;
  GoaObject  *found_object;

  objects = goa_client_get_accounts (self->priv->client);

  found_object = NULL;
  for (node = objects; node != NULL; node = node->next)
    {
      GoaObject *object = GOA_OBJECT (node->data);
      GoaAccount *account;
      const char *provider_type;
      const char *account_identity;

      account = goa_object_peek_account (object);

      if (account == NULL)
        continue;

      provider_type = goa_account_get_provider_type (account);

      if (g_strcmp0 (provider_type, "kerberos") != 0)
        continue;

      if (must_be_enabled)
        {
          GoaTicketing *ticketing;

          ticketing = goa_object_peek_ticketing (object);

          if (ticketing == NULL)
              continue;
        }

      account_identity = goa_account_get_identity (account);

      if (g_strcmp0 (account_identity, principal) == 0)
        {
          found_object = g_object_ref (object);
          break;
        }
    }
  g_list_free_full (objects, (GDestroyNotify) g_object_unref);

  return found_object;
}
