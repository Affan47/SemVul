user_unregister (User *user)
{
        g_dbus_interface_skeleton_unexport (G_DBUS_INTERFACE_SKELETON (user));

        if (user->extension_ids) {
                guint i;

                for (i = 0; i < user->n_extension_ids; i++) {

                        if (user->extension_ids[i] == 0)
                                continue;

                        g_dbus_connection_unregister_object (user->system_bus_connection, user->extension_ids[i]);
                }

                g_clear_pointer (&user->extension_ids, g_free);
                user->n_extension_ids = 0;
        }
}
