send_config_req(Conn_t *conn)
{
        int frame_size;
        struct ctrl_frame *config_req;
        char buff[MAX_CTRL_FRAME];

        diag(COMPONENT, DIAG_DEBUG, "Sending LE_CONFIGURE_REQUEST");


        frame_size = sizeof(struct ctrl_frame);
        if (lec_params.c3_max_frame_size == MTU_1580) frame_size += 5;
        config_req = (struct ctrl_frame *)buff;
        memset(config_req, 0, frame_size);

        prefill_frame(config_req, LE_CONFIG_REQ);
        if (lec_params.c29_v2_capable)
                config_req->header.flags = htons(V2_CAPABLE);
        config_req->src_lan_dst.tag = htons(LAN_DST_MAC_ADDR);
        memcpy(config_req->src_lan_dst.mac, lec_params.c6_mac_addr, ETH_ALEN);
        memcpy(config_req->src_atm_addr, lec_params.c1n_my_atm_addr, ATM_ESA_LEN);
        config_req->lan_type = lec_params.c2_lan_type;
        config_req->max_frame_size = lec_params.c3_max_frame_size;
        config_req->elan_name_size = strlen(lec_params.c5_elan_name);
        if (strlen(lec_params.c5_elan_name) > 0)
                strcpy(config_req->elan_name, lec_params.c5_elan_name);
        if (lec_params.c3_max_frame_size == MTU_1580) {
                lec_params.c3_max_frame_size = MTU_1516;
                *(uint32_t *)(config_req + 1) = htonl(X5_ADJUSTMENT);
                config_req->num_tlvs++;
        }

        if (send_frame(conn, buff, frame_size) != frame_size)
                return -1;

        return 0;
}
