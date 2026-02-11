_disco_in_sess_result(mod_instance_t mi, sess_t sess, pkt_t pkt)
{

    if(pkt->to != NULL && strcmp(jid_user(sess->jid), jid_full(pkt->to)))
    {
        return mod_PASS;
    }


    nad_append_elem(pkt->nad, -1, "identity", 3);
    nad_append_attr(pkt->nad, -1, "category", "account");
    nad_append_attr(pkt->nad, -1, "type", "registered");


    nad_set_attr(pkt->nad, 1, -1, "type", "result", 6);
    pkt_sess(pkt_tofrom(pkt), sess);

    return mod_HANDLED;
}
