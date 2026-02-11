_presence_in_sess(mod_instance_t mi, sess_t sess, pkt_t pkt) {

    if(!(pkt->type & pkt_PRESENCE))
        return mod_PASS;


    if(pkt->from == NULL || jid_compare_user(pkt->from, sess->jid) != 0) {
        if(pkt->from != NULL)
            jid_free(pkt->from);

        pkt->from = jid_dup(sess->jid);
        nad_set_attr(pkt->nad, 1, -1, "from", jid_full(pkt->from), 0);
    }


    if(pkt->to == NULL)
        pres_update(sess, pkt);


    else
        pres_deliver(sess, pkt);

    return mod_HANDLED;
}
