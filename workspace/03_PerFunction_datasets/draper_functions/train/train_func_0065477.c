mca_oob_tcp_peer_accept(mca_oob_tcp_module_t *mod, mca_oob_tcp_peer_t* peer)
{
    opal_output_verbose(OOB_TCP_DEBUG_CONNECT, orte_oob_base_framework.framework_output,
                        "%s tcp:peer_accept called for peer %s in state %s on socket %d",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                        ORTE_NAME_PRINT(&peer->name),
                        mca_oob_tcp_state_print(peer->state), peer->sd);

    if (peer->state != MCA_OOB_TCP_CONNECTED) {

        tcp_peer_event_init(mod, peer);

        if (tcp_peer_send_connect_ack(mod, peer) != ORTE_SUCCESS) {
            opal_output(0, "%s-%s tcp_peer_accept: "
                        "tcp_peer_send_connect_ack failed\n",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                        ORTE_NAME_PRINT(&(peer->name)));
            peer->state = MCA_OOB_TCP_FAILED;
            mca_oob_tcp_peer_close(mod, peer);
            return false;
        }


        ORTE_ACTIVATE_TCP_CMP_OP(mod, &peer->name, mca_oob_tcp_component_set_module);

        tcp_peer_connected(peer);
        if (!peer->recv_ev_active) {
            opal_event_add(&peer->recv_event, 0);
            peer->recv_ev_active = true;
        }

        if (NULL != peer->send_msg && !peer->send_ev_active) {
            opal_event_add(&peer->send_event, 0);
            peer->send_ev_active = true;
        }
        if (OOB_TCP_DEBUG_CONNECT <= opal_output_get_verbosity(orte_oob_base_framework.framework_output)) {
            mca_oob_tcp_peer_dump(peer, "accepted");
        }
        return true;
    }

    opal_output_verbose(OOB_TCP_DEBUG_CONNECT, orte_oob_base_framework.framework_output,
                        "%s tcp:peer_accept ignored for peer %s in state %s on socket %d",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                        ORTE_NAME_PRINT(&peer->name),
                        mca_oob_tcp_state_print(peer->state), peer->sd);
    return false;
}
