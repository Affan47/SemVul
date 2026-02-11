gdm_server_stop (GdmServer *server)
{
        int res;

        if (server->priv->pid <= 1) {
                return TRUE;
        }


        if (server->priv->child_watch_id > 0) {
                g_source_remove (server->priv->child_watch_id);
                server->priv->child_watch_id = 0;
        }

        g_debug ("GdmServer: Stopping server");

        res = gdm_signal_pid (server->priv->pid, SIGTERM);
        if (res < 0) {
        } else {
                server_died (server);
        }

        return TRUE;
}
