listener_config_lock_cb (GSListener *listener,
                         GSMonitor  *monitor)
{
        if (! monitor->priv->prefs->lock_disabled) {
                if (monitor->priv->prefs->ubuntu_lock_on_suspend) {
                        gs_debug ("Locking the screen suspend");
                        gs_monitor_lock_screen (monitor);
                } else {
                        gs_debug ("Locking the screen on suspend disabled by the administrator");
                }
        } else {
                gs_debug ("Locking disabled by the administrator");
        }

}
