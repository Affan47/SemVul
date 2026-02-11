udp_refresh_timer(void * arg) {
    time_t timenow = time(NULL);

    if (slave_cnt > 0) {

        int i = 0;
        int j = 0;
        while (i < slave_cnt) {
            SlaveInfo * s = slave_info + i++;
            if (s->last_packet_time + PEER_DATA_RETENTION_PERIOD >= timenow) {
                if (j < i) slave_info[j] = *s;
                j++;
            }
        }
        slave_cnt = j;
    }

    if (udp_server_port != DISCOVERY_TCF_PORT && last_master_packet_time + PEER_DATA_RETENTION_PERIOD / 2 <= timenow) {

        create_server_socket();
    }


    ifc_cnt = build_ifclist(udp_server_socket, MAX_IFC, ifc_list);

    if (udp_server_port != DISCOVERY_TCF_PORT) {
        int i;
        for (i = 0; i < ifc_cnt; i++) {
            struct sockaddr_in addr;
            memset(&addr, 0, sizeof(addr));
            addr.sin_family = AF_INET;
            addr.sin_port = htons((short)udp_server_port);
            addr.sin_addr.s_addr = ifc_list[i].addr;
            add_slave(&addr, timenow);
        }
    }


    udp_send_all(NULL, NULL);

    post_event_with_delay(udp_refresh_timer, NULL, PEER_DATA_REFRESH_PERIOD * 1000000);
}
