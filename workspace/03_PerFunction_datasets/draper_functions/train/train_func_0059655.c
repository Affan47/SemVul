read_bytes(mca_oob_tcp_peer_t* peer)
{
    int rc;


    while (0 < peer->recv_msg->rdbytes) {
        rc = read(peer->sd, peer->recv_msg->rdptr, peer->recv_msg->rdbytes);
        if (rc < 0) {
            if(opal_socket_errno == EINTR) {
                continue;
            } else if (opal_socket_errno == EAGAIN) {


                return ORTE_ERR_RESOURCE_BUSY;
            } else if (opal_socket_errno == EWOULDBLOCK) {


                return ORTE_ERR_WOULD_BLOCK;
            }


            opal_output_verbose(OOB_TCP_DEBUG_FAIL, orte_oob_base_framework.framework_output,
                                "%s-%s mca_oob_tcp_msg_recv: readv failed: %s (%d)",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                ORTE_NAME_PRINT(&(peer->name)),
                                strerror(opal_socket_errno),
                                opal_socket_errno);


            return ORTE_ERR_COMM_FAILURE;
        } else if (rc == 0)  {


            opal_output_verbose(OOB_TCP_DEBUG_FAIL, orte_oob_base_framework.framework_output,
                                "%s-%s mca_oob_tcp_msg_recv: peer closed connection",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                ORTE_NAME_PRINT(&(peer->name)));

            if (peer->recv_ev_active) {
                opal_event_del(&peer->recv_event);
                peer->recv_ev_active = false;
            }
            if (peer->timer_ev_active) {
                opal_event_del(&peer->timer_event);
                peer->timer_ev_active = false;
            }
            if (peer->send_ev_active) {
                opal_event_del(&peer->send_event);
                peer->send_ev_active = false;
            }
            if (NULL != peer->recv_msg) {
                OBJ_RELEASE(peer->recv_msg);
                peer->recv_msg = NULL;
            }
            mca_oob_tcp_peer_close((mca_oob_tcp_module_t*)peer->mod, peer);


            return ORTE_ERR_WOULD_BLOCK;
        }

        peer->recv_msg->rdbytes -= rc;
        peer->recv_msg->rdptr += rc;
    }


    return ORTE_SUCCESS;
}
