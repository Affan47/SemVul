syncevo_session_get_status (SyncevoSession *session,
                            SyncevoSessionGetStatusCb callback,
                            gpointer userdata)
{
    SessionAsyncData *data;
    SyncevoSessionPrivate *priv;

    priv = GET_PRIVATE (session);

    data = session_async_data_new (session, G_CALLBACK (callback), userdata);

    if (!priv->proxy) {
        if (callback) {
            g_idle_add ((GSourceFunc)get_status_error, data);
        }
        return;
    }

    org_syncevolution_Session_get_status_async
            (priv->proxy,
             (org_syncevolution_Session_get_status_reply) get_status_callback,
             data);
}
