fetion_account_keep_alive(fetion_account *ac)
{

    fetion_sip         *sip;
    sip_header         *eheader;
    gchar              *res;
    gchar              *body;
    fetion_transaction *trans;

    g_return_val_if_fail(ac != NULL, HYBRID_ERROR);

    sip = ac->sip;

    fetion_sip_set_type(sip, SIP_REGISTER);
    eheader = sip_event_header_create(SIP_EVENT_KEEPALIVE);
    fetion_sip_add_header(sip, eheader);

    trans = transaction_create();
    transaction_set_callid(trans, sip->callid);
    transaction_set_callback(trans, keep_alive_cb);
    transaction_add(ac, trans);

    body = generate_keep_alive_body();
    res = fetion_sip_to_string(sip , body);
    g_free(body);

    hybrid_debug_info("fetion", "keep alive,send:\n%s", res);

    if (send(ac->sk, res, strlen(res), 0) == -1) {
        g_free(res);
        return HYBRID_ERROR;
    }

    g_free(res);

    return HYBRID_OK;
}
