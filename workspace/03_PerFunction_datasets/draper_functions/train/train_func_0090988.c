accounts_user_set_hidden (AccountsUser *user, gboolean hidden, gboolean emit_signal)
{
    GError *error = NULL;

    user->hidden = hidden;

    if (user->hidden && user->id != 0)
    {
        g_dbus_connection_unregister_object (accounts_connection, user->id);
        g_dbus_connection_emit_signal (accounts_connection,
                                       NULL,
                                       "/org/freedesktop/Accounts",
                                       "org.freedesktop.Accounts",
                                       "UserDeleted",
                                       g_variant_new ("(o)", user->path),
                                       &error);
        if (error)
            g_warning ("Failed to emit UserDeleted: %s", error->message);
        g_clear_error (&error);

        user->id = 0;
    }
    if (!user->hidden && user->id == 0)
    {
        user->id = g_dbus_connection_register_object (accounts_connection,
                                                      user->path,
                                                      user_info->interfaces[0],
                                                      &user_vtable,
                                                      user,
                                                      NULL,
                                                      &error);
        if (error)
            g_warning ("Failed to register user: %s", error->message);
        g_clear_error (&error);

        g_dbus_connection_emit_signal (accounts_connection,
                                       NULL,
                                       "/org/freedesktop/Accounts",
                                       "org.freedesktop.Accounts",
                                       "UserAdded",
                                       g_variant_new ("(o)", user->path),
                                       &error);
        if (error)
            g_warning ("Failed to emit UserAdded: %s", error->message);
        g_clear_error (&error);
    }
}
