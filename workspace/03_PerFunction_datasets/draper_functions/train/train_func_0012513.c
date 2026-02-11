handle_user_call (GDBusConnection       *connection,
                  const gchar           *sender,
                  const gchar           *object_path,
                  const gchar           *interface_name,
                  const gchar           *method_name,
                  GVariant              *parameters,
                  GDBusMethodInvocation *invocation,
                  gpointer               user_data)
{
    AccountsUser *user = user_data;

    if (strcmp (method_name, "SetXSession") == 0)
    {
        gchar *xsession;

        g_variant_get (parameters, "(&s)", &xsession);

        g_free (user->xsession);
        user->xsession = g_strdup (xsession);

        g_dbus_method_invocation_return_value (invocation, g_variant_new ("()"));


        g_dbus_connection_emit_signal (accounts_connection,
                                       NULL,
                                       user->path,
                                       "org.freedesktop.Accounts.User",
                                       "Changed",
                                       g_variant_new ("()"),
                                       NULL);
    }
    else
        g_dbus_method_invocation_return_error (invocation, G_DBUS_ERROR, G_DBUS_ERROR_FAILED, "No such method: %s", method_name);
}
