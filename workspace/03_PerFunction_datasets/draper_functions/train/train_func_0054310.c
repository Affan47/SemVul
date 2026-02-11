udp_die(void)
{
    Udpc *udpc;

    if (!udp_running) return -1;


    debug("bb.udp", 0, "udp_die: removing producers from udp-lists");

    while((udpc = gwlist_consume(udpc_list)) != NULL) {
	gwlist_remove_producer(udpc->outgoing_list);
    }
    gwlist_destroy(udpc_list, NULL);
    udp_running = 0;

    octstr_destroy(allow_ip);
    octstr_destroy(deny_ip);
    allow_ip = NULL;
    deny_ip = NULL;

    return 0;
}
