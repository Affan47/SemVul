_iq_vcard_pkt_sm(mod_instance_t mi, pkt_t pkt) {
    os_t os;
    st_ret_t ret;
    pkt_t result;


    if((pkt->type != pkt_IQ && pkt->type != pkt_IQ_SET) || pkt->ns != ns_VCARD)
        return mod_PASS;


    if(pkt->type == pkt_IQ_SET)
        return -stanza_err_FORBIDDEN;


    ret = storage_get(mi->sm->st, "vcard", pkt->to->domain, NULL, &os);
    switch(ret) {
        case st_FAILED:
            return -stanza_err_INTERNAL_SERVER_ERROR;

        case st_NOTIMPL:
            return -stanza_err_FEATURE_NOT_IMPLEMENTED;

        case st_NOTFOUND:
            return -stanza_err_ITEM_NOT_FOUND;

        case st_SUCCESS:
            result = _iq_vcard_to_pkt(mi->sm, os);
            os_free(os);

            result->to = jid_dup(pkt->from);
            result->from = jid_dup(pkt->to);

            nad_set_attr(result->nad, 1, -1, "to", jid_full(result->to), 0);
            nad_set_attr(result->nad, 1, -1, "from", jid_full(result->from), 0);

            pkt_id(pkt, result);

            pkt_router(result);

            pkt_free(pkt);

            return mod_HANDLED;
    }


    pkt_free(pkt);
    return mod_HANDLED;
}
