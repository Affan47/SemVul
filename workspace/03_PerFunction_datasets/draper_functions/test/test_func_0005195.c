udp_start(Cfg *cfg)
{

    if (udp_running) return -1;

    debug("wap.proxy", 0, "starting UDP sender/receiver module");

    udpc_list = gwlist_create();

    add_service(server_port, octstr_get_cstr(interface_name), NULL);

    gwlist_add_producer(incoming_wdp);
    udp_running = 1;
    return 0;
}
