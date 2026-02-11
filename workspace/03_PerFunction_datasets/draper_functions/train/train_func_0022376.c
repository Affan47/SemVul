wdp_router(void *arg)
{
    Msg *msg;

    gwlist_add_producer(flow_threads);

    while (bb_status != BB_DEAD) {

        if ((msg = gwlist_consume(outgoing_wdp)) == NULL)
            break;

        gw_assert(msg_type(msg) == wdp_datagram);


        udp_addwdp(msg);
    }
    udp_die();


    gwlist_remove_producer(flow_threads);
}
