set_status (GSWatcher *watcher,
            guint      status)
{
        gboolean is_idle;

        if (! watcher->priv->active) {
                gs_debug ("GSWatcher: not active, ignoring status changes");
                return;
        }

        is_idle = (status == 3);

        if (!is_idle && !watcher->priv->idle_notice) {

                return;
        }

        if (is_idle) {
                _gs_watcher_set_session_idle_notice (watcher, is_idle);

                if (watcher->priv->idle_id > 0) {
                        g_source_remove (watcher->priv->idle_id);
                }
                watcher->priv->idle_id = g_timeout_add (watcher->priv->delta_notice_timeout,
                                                        (GSourceFunc)on_idle_timeout,
                                                        watcher);
        } else {

                if (watcher->priv->idle_id > 0) {
                        g_source_remove (watcher->priv->idle_id);
                }
                _gs_watcher_set_session_idle (watcher, FALSE);
                _gs_watcher_set_session_idle_notice (watcher, FALSE);
        }
}
