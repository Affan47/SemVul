accounts_user_call_set_home_directory_sync (
    AccountsUser *proxy,
    const gchar *arg_homedir,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "SetHomeDirectory",
    g_variant_new ("(s)",
                   arg_homedir),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "()");
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}
