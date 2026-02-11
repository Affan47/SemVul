gdm_client_open_reauthentication_channel_sync (GdmClient     *client,
                                               const char    *username,
                                               GCancellable  *cancellable,
                                               GError       **error)
{
        GDBusConnection *connection;
        GdmUserVerifier *user_verifier = NULL;
        gboolean         ret;
        char            *address;

        g_return_val_if_fail (GDM_IS_CLIENT (client), FALSE);

        if (client->priv->manager == NULL) {
                client->priv->manager = gdm_manager_proxy_new_for_bus_sync (G_BUS_TYPE_SYSTEM,
                                                                            G_DBUS_PROXY_FLAGS_NONE,
                                                                            "org.gnome.DisplayManager",
                                                                            "/org/gnome/DisplayManager/Manager",
                                                                            cancellable,
                                                                            error);

                if (client->priv->manager == NULL) {
                        goto out;
                }
        } else {
                client->priv->manager = g_object_ref (client->priv->manager);
        }

        ret = gdm_manager_call_open_reauthentication_channel_sync (client->priv->manager,
                                                                   username,
                                                                   &address,
                                                                   cancellable,
                                                                   error);

        if (!ret) {
                goto out;
        }

        g_debug ("GdmClient: connecting to address: %s", client->priv->address);

        connection = g_dbus_connection_new_for_address_sync (address,
                                                             G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT,
                                                             NULL,
                                                             cancellable,
                                                             error);

        if (connection == NULL) {
                g_free (address);
                goto out;
        }
        g_free (address);

        user_verifier = gdm_user_verifier_proxy_new_sync (connection,
                                                          G_DBUS_PROXY_FLAGS_NONE,
                                                          NULL,
                                                          SESSION_DBUS_PATH,
                                                          cancellable,
                                                          error);

        if (user_verifier != NULL) {
                g_object_weak_ref (G_OBJECT (user_verifier),
                                   (GWeakNotify)
                                   g_object_unref,
                                   connection);

                g_object_weak_ref (G_OBJECT (user_verifier),
                                   (GWeakNotify)
                                   g_clear_object,
                                   &client->priv->manager);
        }

 out:
        return user_verifier;
}
