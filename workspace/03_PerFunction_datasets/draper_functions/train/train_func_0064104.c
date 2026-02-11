do_started(long long action,
           enum crmd_fsa_cause cause,
           enum crmd_fsa_state cur_state, enum crmd_fsa_input current_input, fsa_data_t * msg_data)
{
    static struct qb_ipcs_service_handlers crmd_callbacks = {
        .connection_accept = crmd_ipc_accept,
        .connection_created = crmd_ipc_created,
        .msg_process = crmd_ipc_dispatch,
        .connection_closed = crmd_ipc_closed,
        .connection_destroyed = crmd_ipc_destroy
    };

    if (cur_state != S_STARTING) {
        crm_err("Start cancelled... %s", fsa_state2string(cur_state));
        return;

    } else if (is_set(fsa_input_register, R_MEMBERSHIP) == FALSE) {
        crm_info("Delaying start, no membership data (%.16llx)", R_MEMBERSHIP);

        crmd_fsa_stall(TRUE);
        return;

    } else if (is_set(fsa_input_register, R_LRM_CONNECTED) == FALSE) {
        crm_info("Delaying start, LRM not connected (%.16llx)", R_LRM_CONNECTED);

        crmd_fsa_stall(TRUE);
        return;

    } else if (is_set(fsa_input_register, R_CIB_CONNECTED) == FALSE) {
        crm_info("Delaying start, CIB not connected (%.16llx)", R_CIB_CONNECTED);

        crmd_fsa_stall(TRUE);
        return;

    } else if (is_set(fsa_input_register, R_READ_CONFIG) == FALSE) {
        crm_info("Delaying start, Config not read (%.16llx)", R_READ_CONFIG);

        crmd_fsa_stall(TRUE);
        return;

    } else if (is_set(fsa_input_register, R_PEER_DATA) == FALSE) {


        crm_info("Delaying start, No peer data (%.16llx)", R_PEER_DATA);

#if SUPPORT_HEARTBEAT
        if (is_heartbeat_cluster()) {
            HA_Message *msg = NULL;

            crm_trace("Looking for a HA message");
            msg = fsa_cluster_conn->llc_ops->readmsg(fsa_cluster_conn, 0);
            if (msg != NULL) {
                crm_trace("There was a HA message");
                ha_msg_del(msg);
            }
        }
#endif
        crmd_fsa_stall(TRUE);
        return;
    }

    crm_debug("Init server comms");
    ipcs = crmd_ipc_server_init(&crmd_callbacks);
    if (ipcs == NULL) {
        crm_err("Failed to create IPC server: shutting down and inhibiting respawn");
        register_fsa_error(C_FSA_INTERNAL, I_ERROR, NULL);
    }

    if (stonith_reconnect == NULL) {
        int dummy;

        stonith_reconnect = mainloop_add_trigger(G_PRIORITY_LOW, te_connect_stonith, &dummy);
    }
    set_bit(fsa_input_register, R_ST_REQUIRED);
    mainloop_set_trigger(stonith_reconnect);

    crm_notice("The local CRM is operational");
    clear_bit(fsa_input_register, R_STARTING);
    register_fsa_input(msg_data->fsa_cause, I_PENDING, NULL);
}
