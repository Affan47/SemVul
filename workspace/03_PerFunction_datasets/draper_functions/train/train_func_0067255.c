_deliver_in_sess(mod_instance_t mi, sess_t sess, pkt_t pkt)
{

    if(pkt->from == NULL || jid_compare_user(pkt->from, sess->jid) != 0) {
        if(pkt->from != NULL)
            jid_free(pkt->from);

        pkt->from = jid_dup(sess->jid);
        nad_set_attr(pkt->nad, 1, -1, "from", jid_full(pkt->from), 0);
    }


    if(pkt->to == NULL) {


        if(pkt->type == pkt_IQ_RESULT) {
            pkt_free(pkt);
            return mod_HANDLED;
        }


        if(pkt->type & pkt_IQ) {
            return -stanza_err_FEATURE_NOT_IMPLEMENTED;
        }


        pkt->to = jid_dup(sess->jid);
        nad_set_attr(pkt->nad, 1, -1, "to", jid_full(pkt->to), 0);
    }


    pkt_router(pkt);

    return mod_HANDLED;
}
