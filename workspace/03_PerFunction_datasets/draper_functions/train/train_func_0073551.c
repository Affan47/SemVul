fetion_buddy_handle_request(fetion_account *ac, const gchar *sipuri,
                            const gchar *userid, const gchar *alias, const gchar *groupid,
                            gboolean accept)
{
    fetion_sip         *sip;
    sip_header         *eheader;
    gchar              *body;
    gchar              *sip_text;
    fetion_transaction *trans;

    g_return_if_fail(ac != NULL);
    g_return_if_fail(sipuri != NULL);
    g_return_if_fail(userid != NULL);
    g_return_if_fail(groupid != NULL);

    sip = ac->sip;

    fetion_sip_set_type(sip, SIP_SERVICE);
    eheader = sip_event_header_create(SIP_EVENT_HANDLECONTACTREQUEST);

    if (accept) {
        trans = transaction_create();
        transaction_set_callid(trans, sip->callid);
        transaction_set_userid(trans, userid);
        transaction_set_callback(trans, handle_request_cb);
        transaction_add(ac, trans);
    }

    fetion_sip_add_header(sip, eheader);
    body = generate_handle_request_body(sipuri, userid, alias, groupid, accept);

    sip_text = fetion_sip_to_string(sip, body);
    g_free(body);

    if (send(ac->sk, sip_text, strlen(sip_text), 0) == -1) {

        hybrid_debug_error("fetion", "handle buddy request failed.");
        g_free(sip_text);

        return;
    }

    g_free(sip_text);
}
