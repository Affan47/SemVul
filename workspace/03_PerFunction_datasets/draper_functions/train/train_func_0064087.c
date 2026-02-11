pkt_tofrom(pkt_t pkt) {
    jid_t tmp;

    if(pkt == NULL) return NULL;


    tmp = pkt->from;
    pkt->from = pkt->to;
    pkt->to = tmp;
    tmp = pkt->rfrom;
    pkt->rfrom = pkt->rto;
    pkt->rto = tmp;


    if(pkt->to != NULL)
        nad_set_attr(pkt->nad, 1, -1, "to", jid_full(pkt->to), 0);
    if(pkt->from != NULL)
        nad_set_attr(pkt->nad, 1, -1, "from", jid_full(pkt->from), 0);
    if(pkt->rto != NULL)
        nad_set_attr(pkt->nad, 0, -1, "to", jid_full(pkt->rto), 0);
    if(pkt->rfrom != NULL)
        nad_set_attr(pkt->nad, 0, -1, "from", jid_full(pkt->rfrom), 0);

    return pkt;
}
