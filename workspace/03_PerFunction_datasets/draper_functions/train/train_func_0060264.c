polkit_authority_authentication_agent_response (PolkitAuthority      *authority,
                                                const gchar          *cookie,
                                                PolkitIdentity       *identity,
                                                GCancellable         *cancellable,
                                                GAsyncReadyCallback   callback,
                                                gpointer              user_data)
{
  GVariant *identity_value;

  g_return_if_fail (POLKIT_IS_AUTHORITY (authority));
  g_return_if_fail (cookie != NULL);
  g_return_if_fail (POLKIT_IS_IDENTITY (identity));
  g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

  identity_value = polkit_identity_to_gvariant (identity);
  g_variant_ref_sink (identity_value);
  g_dbus_proxy_call (authority->proxy,
                     "AuthenticationAgentResponse",
                     g_variant_new ("(s@(sa{sv}))",
                                    cookie,
                                    identity_value),
                     G_DBUS_CALL_FLAGS_NONE,
                     -1,
                     cancellable,
                     generic_async_cb,
                     g_simple_async_result_new (G_OBJECT (authority),
                                                callback,
                                                user_data,
                                                polkit_authority_authentication_agent_response));
  g_variant_unref (identity_value);
}
