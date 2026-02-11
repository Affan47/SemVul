tls_conn_cb(HybridSslConnection *ssl, XmppStream *stream)
{
    gchar *msg;

    hybrid_account_set_connection_string(stream->account->account,
                                         _("TLS connection established."));

    msg = create_initiate_stream(stream);


    xmpp_stream_set_id(stream, NULL);
    xmpp_stream_set_state(stream, XMPP_STATE_TLS_STREAM_STARTING);

    hybrid_debug_info("stream", "send start stream request:\n%s", msg);

    if (hybrid_ssl_write(ssl, msg, strlen(msg)) == -1) {

        hybrid_account_error_reason(stream->account->account,
                                    _("send initial jabber request failed"));
        g_free(msg);

        return FALSE;
    }

    g_free(msg);

    return FALSE;
}
