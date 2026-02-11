handle_login1_session_call (GDBusConnection       *connection,
                            const gchar           *sender,
                            const gchar           *object_path,
                            const gchar           *interface_name,
                            const gchar           *method_name,
                            GVariant              *parameters,
                            GDBusMethodInvocation *invocation,
                            gpointer               user_data)
{
    Login1Session *session = user_data;

    if (strcmp (method_name, "Lock") == 0)
    {
        if (!session->locked)
            check_status ("LOGIN1 LOCK-SESSION");
        session->locked = TRUE;
        g_dbus_method_invocation_return_value (invocation, g_variant_new ("()"));
    }
    else if (strcmp (method_name, "Unlock") == 0)
    {
        if (session->locked)
            check_status ("LOGIN1 UNLOCK-SESSION");
        session->locked = FALSE;
        g_dbus_method_invocation_return_value (invocation, g_variant_new ("()"));
    }
    else if (strcmp (method_name, "Activate") == 0)
    {
        gchar *status = g_strdup_printf ("LOGIN1 ACTIVATE-SESSION SESSION=%s", strrchr (object_path, '/') + 1);
        check_status (status);
        g_free (status);

        g_dbus_method_invocation_return_value (invocation, g_variant_new ("()"));
    }
    else
        g_dbus_method_invocation_return_error (invocation, G_DBUS_ERROR, G_DBUS_ERROR_FAILED, "No such method: %s", method_name);
}
