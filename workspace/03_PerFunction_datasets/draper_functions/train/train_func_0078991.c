gnome_xsettings_manager_stop (GnomeXSettingsManager *manager)
{
        GnomeXSettingsManagerPrivate *p = manager->priv;
        int i;

        g_debug ("Stopping xsettings manager");

        if (manager->priv->shell_name_watch_id > 0)
                g_bus_unwatch_name (manager->priv->shell_name_watch_id);

        if (manager->priv->unity_name_watch_id > 0)
                g_bus_unwatch_name (manager->priv->unity_name_watch_id);

        if (p->managers != NULL) {
                for (i = 0; p->managers [i]; ++i)
                        xsettings_manager_destroy (p->managers [i]);

                g_free (p->managers);
                p->managers = NULL;
        }

        if (p->plugin_settings != NULL) {
                g_object_unref (p->plugin_settings);
                p->plugin_settings = NULL;
        }

        stop_fontconfig_monitor (manager);

        if (p->settings != NULL) {
                g_hash_table_destroy (p->settings);
                p->settings = NULL;
        }

        if (p->gtk != NULL) {
                g_object_unref (p->gtk);
                p->gtk = NULL;
        }
}
