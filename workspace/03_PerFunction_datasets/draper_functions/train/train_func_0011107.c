auth_success(XmppStream *stream)
{
    HybridAccount *account;

    g_return_if_fail(stream != NULL);

    account = stream->account->account;

    if (account->state == HYBRID_STATE_OFFLINE ||
        account->state == HYBRID_STATE_INVISIBLE) {
        account->state = HYBRID_STATE_ONLINE;
    }


    hybrid_account_set_state(account, account->state);


    hybrid_account_set_connection_status(account,
            HYBRID_CONNECTION_CONNECTED);


    xmpp_stream_get_vcard(stream);
    xmpp_stream_get_roster(stream);

}
