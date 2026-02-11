fetion_buddy_remove(fetion_account *ac, const gchar *userid)
{
    fetion_sip *sip;
    sip_header *eheader;
    gchar      *res;
    gchar      *body;

    g_return_val_if_fail(ac != NULL, HYBRID_ERROR);
    g_return_val_if_fail(userid != NULL, HYBRID_ERROR);

    sip = ac->sip;

    fetion_sip_set_type(sip, SIP_SERVICE);
    eheader = sip_event_header_create(SIP_EVENT_DELETEBUDDY);
    fetion_sip_add_header(sip, eheader);

    body = generate_remove_buddy_body(userid);
    res = fetion_sip_to_string(sip, body);
    g_free(body);

    hybrid_debug_info("fetion", "remove buddy, send:\n%s", res);

    if (send(ac->sk, res, strlen(res), 0) == -1) {
        hybrid_debug_error("fetion", "remove buddy %s", userid);

        return HYBRID_ERROR;
    }

    g_free(res);

    return HYBRID_OK;
}
