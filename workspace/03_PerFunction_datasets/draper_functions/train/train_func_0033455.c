get_mute_reply (DBusGProxy *proxy,
                gboolean    OUT_mute,
                GError     *error,
                gpointer    userdata)
{
    struct _AsyncClosure *data = (struct _AsyncClosure *) userdata;
    BrQueueGetMuteCallback cb;

    cb = (BrQueueGetMuteCallback) (data->cb);

    if (error) {
        OUT_mute = 0.0;
    }

    cb (data->queue, OUT_mute, error, data->userdata);

    if (error) {
        g_error_free (error);
    }

    g_free (data);
}
