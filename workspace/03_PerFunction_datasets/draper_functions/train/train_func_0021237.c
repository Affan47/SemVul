tpaw_keyring_get_account_password_async (TpAccount *account,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  GSimpleAsyncResult *simple;
  const gchar *account_id;

  g_return_if_fail (TP_IS_ACCOUNT (account));
  g_return_if_fail (callback != NULL);

  simple = g_simple_async_result_new (G_OBJECT (account), callback,
      user_data, tpaw_keyring_get_account_password_async);

  account_id = tp_proxy_get_object_path (account) +
    strlen (TP_ACCOUNT_OBJECT_PATH_BASE);

  DEBUG ("Trying to get password for: %s", account_id);

#ifdef HAVE_UOA
    {
      const gchar *provider;

      provider = tp_account_get_storage_provider (account);
      if (!tp_strdiff (provider, TPAW_UOA_PROVIDER))
        {
          uoa_get_account_password (account, simple);
          g_object_unref (simple);
          return;
        }
    }
#endif

  secret_password_lookup (&account_keyring_schema, NULL,
          lookup_item_cb, simple,
          "account-id", account_id,
          "param-name", "password",
          NULL);
}
