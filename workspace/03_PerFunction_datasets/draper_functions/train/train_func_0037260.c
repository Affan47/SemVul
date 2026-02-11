fetion_message_send(fetion_account *account, const gchar *userid,
                    const gchar *text)
{
    fetion_sip   *sip;
    sip_header   *toheader;
    sip_header   *cheader;
    sip_header   *kheader;
    sip_header   *nheader;
    gchar        *sip_text;
    fetion_buddy *buddy;

    g_return_val_if_fail(account != NULL, HYBRID_ERROR);
    g_return_val_if_fail(userid != NULL && *userid != '\0', HYBRID_ERROR);
    g_return_val_if_fail(text != NULL, HYBRID_ERROR);

    sip = account->sip;

    if (!(buddy = fetion_buddy_find_by_userid(account, userid))) {
        hybrid_debug_error("fetion", "FATAL, can't find specified buddy");

        return HYBRID_ERROR;
    }

    fetion_transaction *trans = transaction_create();

    transaction_set_userid(trans, userid);
    transaction_set_msg(trans, text);

    if (!account->channel_ready) {


        transaction_wait(account, trans);

        hybrid_debug_info("fetion", "channel not ready, transaction sleep.");

        return HYBRID_OK;
    }

    fetion_sip_set_type(sip, SIP_MESSAGE);

    nheader  = sip_event_header_create(SIP_EVENT_CATMESSAGE);
    toheader = sip_header_create("T", buddy->sipuri);
    cheader  = sip_header_create("C", "text/plain");
    kheader  = sip_header_create("K", "SaveHistory");
    fetion_sip_add_header(sip, toheader);
    fetion_sip_add_header(sip, cheader);
    fetion_sip_add_header(sip, kheader);
    fetion_sip_add_header(sip, nheader);

    transaction_set_callid(trans, sip->callid);
    transaction_set_callback(trans, sms_response_cb);

    transaction_set_data(trans, account);
    transaction_set_timeout(trans, (GSourceFunc)sms_timeout_cb, trans);
    transaction_add(account, trans);

    sip_text = fetion_sip_to_string(sip, text);

    hybrid_debug_info("fetion", "send message, send:\n%s", sip_text);

    if (send(account->sk, sip_text, strlen(sip_text), 0) == -1) {
        g_free(sip_text);

        return HYBRID_ERROR;
    }

    g_free(sip_text);

    return HYBRID_OK;
}
