xmpp_stream_ping(XmppStream *stream)
{
    IqRequest *iq;
    xmlnode   *node;

    g_return_val_if_fail(stream != NULL, HYBRID_ERROR);

    iq = iq_request_create(stream, IQ_TYPE_GET);

    node = xmlnode_new_child(iq->node, "ping");
    xmlnode_new_namespace(node, NULL, NS_XMPP_PING);

    iq_request_set_callback(iq, ping_cb, NULL);

    if (stream->keepalive_source) {
        g_source_remove(stream->keepalive_source);
    }

    stream->keepalive_source =
        g_timeout_add_seconds(60, (GSourceFunc)ping_timeout_cb, stream);

    if (iq_request_send(iq) != HYBRID_OK) {

        hybrid_debug_error("xmpp", "ping xmpp server failed.");

        iq_request_destroy(iq);

        hybrid_account_error_reason(stream->account->account,
                                    _("Connection Closed."));

        return HYBRID_ERROR;
    }

    iq_request_destroy(iq);

    return HYBRID_OK;
}
