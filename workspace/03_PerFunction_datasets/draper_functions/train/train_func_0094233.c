session_changed_cb (SyncevoServer *server,
                    char *path,
                    gboolean started,
                    SyncConfigWidget *self)
{
    if (started) {
        set_session (self, path);
    } else if (g_strcmp0 (self->running_session, path) == 0 ) {
        set_session (self, NULL);
    }
}
