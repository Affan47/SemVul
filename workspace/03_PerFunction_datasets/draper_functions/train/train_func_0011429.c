gsd_orientation_manager_stop (GsdOrientationManager *manager)
{
        GsdOrientationManagerPrivate *p = manager->priv;

        g_debug ("Stopping orientation manager");

        if (p->settings) {
                g_object_unref (p->settings);
                p->settings = NULL;
        }

        if (p->sysfs_path) {
                g_free (p->sysfs_path);
                p->sysfs_path = NULL;
        }

        if (p->introspection_data) {
                g_dbus_node_info_unref (p->introspection_data);
                p->introspection_data = NULL;
        }

        if (p->client) {
                g_object_unref (p->client);
                p->client = NULL;
        }
}
