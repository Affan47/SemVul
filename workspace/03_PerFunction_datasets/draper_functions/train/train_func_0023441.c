gsd_cursor_manager_stop (GsdCursorManager *manager)
{
        GdkDeviceManager *device_manager;

        g_debug ("Stopping cursor manager");

        device_manager = gdk_display_get_device_manager (gdk_display_get_default ());

        if (manager->priv->added_id > 0) {
                g_signal_handler_disconnect (G_OBJECT (device_manager), manager->priv->added_id);
                manager->priv->added_id = 0;
        }

        if (manager->priv->removed_id > 0) {
                g_signal_handler_disconnect (G_OBJECT (device_manager), manager->priv->removed_id);
                manager->priv->removed_id = 0;
        }

        if (manager->priv->changed_id > 0) {
                g_signal_handler_disconnect (G_OBJECT (device_manager), manager->priv->changed_id);
                manager->priv->changed_id = 0;
        }

        if (manager->priv->cursor_shown == FALSE)
                set_cursor_visibility (manager, TRUE);
}
