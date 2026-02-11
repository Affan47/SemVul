les_connect(int lecs_method, struct sockaddr_atmsvc *manual_atm_addr,
                  struct sockaddr_atmsvc *listen_addr)
{
        struct sockaddr_atmsvc les_addr;
        struct atm_sap sap;
        struct atm_qos qos;
        char buff[MAX_CTRL_FRAME];
        int frame_size = 0;

        diag(COMPONENT, DIAG_DEBUG, "Entering Join phase");

        if (lecs_method == LECS_NONE) {
                diag(COMPONENT, DIAG_DEBUG, "Skipping LECS, connecting straight to LES");
                memcpy(les_addr.sas_addr.prv, manual_atm_addr->sas_addr.prv, ATM_ESA_LEN);
        } else memcpy(les_addr.sas_addr.prv, lec_params.c9_les_atm_addr, ATM_ESA_LEN);
	*les_addr.sas_addr.pub = 0;

        init_conn_params(&sap, &qos, CONTROL_CONN);
        lec_params.ctrl_direct = setup_svc(&les_addr, listen_addr, &sap, &qos);
        if (lec_params.ctrl_direct == NULL) {
                diag(COMPONENT, DIAG_ERROR, "Control direct SVC failed");
                random_delay();
                return -1;
        }
        lec_params.ctrl_listen = create_listensocket(listen_addr, &sap, &qos);
        if (lec_params.ctrl_listen == NULL) {
                diag(COMPONENT, DIAG_ERROR, "Control distribute listen socket failed");
                random_delay();
                return -1;
        }

        lec_params.c7c_current_timeout = lec_params.c7i_initial_ctrl_timeout;
        while (lec_params.c7c_current_timeout <= lec_params.c7_ctrl_timeout) {
                if (send_join_req(lec_params.ctrl_direct) < 0) {
                        diag(COMPONENT, DIAG_ERROR, "Sending LE_JOIN_REQUEST failed");
                        random_delay();
                        return -1;
                }
                frame_size = read_join_rsp(buff, sizeof(buff));
                if (frame_size < 0) {
                        diag(COMPONENT, DIAG_ERROR, "Receiving LE_JOIN_RESPONSE failed");
                        random_delay();
                        return -1;
                } else if (frame_size == 0)
                        lec_params.c7c_current_timeout *= lec_params.c7x_timeout_multiplier;
                else
                        break;
        }
        lec_params.c7c_current_timeout = lec_params.c7i_initial_ctrl_timeout;
        if (frame_size == 0) {
                diag(COMPONENT, DIAG_ERROR, "LE_JOIN_RESPONSE timed out");
                return -1;
        }

        if (parse_join_rsp(buff, frame_size) < 0) {
                diag(COMPONENT, DIAG_ERROR, "Parsing LE_JOIN_RESPONSE failed");
                return -1;
        }

        return 0;
}
