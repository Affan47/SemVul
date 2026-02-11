accounts_accounts_call_create_user_sync (
    AccountsAccounts *proxy,
    const gchar *arg_name,
    const gchar *arg_fullname,
    gint arg_accountType,
    gchar **out_user,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "CreateUser",
    g_variant_new ("(ssi)",
                   arg_name,
                   arg_fullname,
                   arg_accountType),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(o)",
                 out_user);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}
