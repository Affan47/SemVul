xmpp_keep_alive(HybridAccount *account)
{
    XmppStream *stream;

    stream = hybrid_account_get_protocol_data(account);

    if (xmpp_stream_ping(stream) != HYBRID_OK) {
        printf("%s\n", "error");
        return FALSE;
    }

    return TRUE;
}
