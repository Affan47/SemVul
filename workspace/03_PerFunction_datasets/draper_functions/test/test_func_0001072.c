emit_removals_in_idle (CkFileMonitor *monitor)
{
        gpointer          wd_p;
        FileInotifyWatch *watch;
        GSList           *l;

        monitor->priv->remove_idle_id = 0;

        while ((wd_p = g_queue_pop_head (monitor->priv->remove_events)) != NULL) {
                watch = g_hash_table_lookup (monitor->priv->wd_to_watch, wd_p);
                if (watch && watch->wd != -1) {
                    for (l = watch->notifies; l != NULL; l = l->next) {
                            FileMonitorNotify *notify;

                            notify = g_hash_table_lookup (monitor->priv->notifies,
                                                          GUINT_TO_POINTER (l->data));
                            if (notify == NULL) {
                                    continue;
                            }
                            notify->watch = NULL;
                    }
                    file_monitor_remove_watch (monitor, watch);
                    g_free (watch);
                }
        }

        return FALSE;
}
