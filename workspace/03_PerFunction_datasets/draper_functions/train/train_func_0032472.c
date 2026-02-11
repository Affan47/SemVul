main (int argc, char **argv)
{
  GError *error = NULL;
  GoaClient *client;
  GList *accounts, *l;
  GoaAccount *account;

  client = goa_client_new_sync (NULL, &error);
  if (!client) {
    g_error ("Could not create GoaClient: %s", error->message);
    return 1;
  }

  accounts = goa_client_get_accounts (client);
  for (l = accounts; l != NULL; l = l->next) {
    account = goa_object_get_account (GOA_OBJECT (l->data));
    g_print ("%s at %s\n",
             goa_account_get_presentation_identity (account),
             goa_account_get_provider_name (account));
  }

  g_list_free_full (accounts, (GDestroyNotify) g_object_unref);

  return 0;
}
