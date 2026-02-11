server_handle_authentication_agent_response (Server                 *server,
                                             GVariant               *parameters,
                                             PolkitSubject          *caller,
                                             GDBusMethodInvocation  *invocation)
{
  const gchar *cookie;
  GVariant *identity_gvariant;
  PolkitIdentity *identity;
  GError *error;

  identity = NULL;

  g_variant_get (parameters,
                 "(&s@(sa{sv}))",
                 &cookie,
                 &identity_gvariant);

  error = NULL;
  identity = polkit_identity_new_for_gvariant (identity_gvariant, &error);
  if (identity == NULL)
    {
      g_prefix_error (&error, "Error getting identity: ");
      g_dbus_method_invocation_return_gerror (invocation, error);
      g_error_free (error);
      goto out;
    }

  error = NULL;
  if (!polkit_backend_authority_authentication_agent_response (server->authority,
                                                               caller,
                                                               cookie,
                                                               identity,
                                                               &error))
    {
      g_dbus_method_invocation_return_gerror (invocation, error);
      g_error_free (error);
      goto out;
    }

  g_dbus_method_invocation_return_value (invocation, g_variant_new ("()"));

 out:
  if (identity != NULL)
    g_object_unref (identity);
}
