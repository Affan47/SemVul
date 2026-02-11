mca_btl_sctp_endpoint_accept(mca_btl_base_endpoint_t* btl_endpoint, struct sockaddr_in* addr, int sd)
{
    if(mca_btl_sctp_component.sctp_if_11) {

        mca_btl_sctp_addr_t* btl_addr;
        mca_btl_sctp_proc_t* this_proc = mca_btl_sctp_proc_local();
        int cmpval;

        OPAL_THREAD_LOCK(&btl_endpoint->endpoint_recv_lock);
        OPAL_THREAD_LOCK(&btl_endpoint->endpoint_send_lock);
        if(((btl_addr = btl_endpoint->endpoint_addr) != NULL) &&
           btl_addr->addr_inet.s_addr == addr->sin_addr.s_addr)
        {
            mca_btl_sctp_proc_t *endpoint_proc = btl_endpoint->endpoint_proc;
            cmpval = ompi_rte_compare_name_fields(OMPI_RTE_CMP_ALL,
                    &endpoint_proc->proc_ompi->proc_name,
                    &this_proc->proc_ompi->proc_name);
            if((btl_endpoint->endpoint_sd < 0) ||
                    (btl_endpoint->endpoint_state != MCA_BTL_SCTP_CONNECTED &&
                     cmpval < 0)) {
                mca_btl_sctp_endpoint_close(btl_endpoint);
                SCTP_BTL_ERROR(("endpoint_close in endpoint_accept #1\n"));
                btl_endpoint->endpoint_sd = sd;
                if(mca_btl_sctp_endpoint_send_connect_ack(btl_endpoint) != OMPI_SUCCESS) {
                    mca_btl_sctp_endpoint_close(btl_endpoint);
                    SCTP_BTL_ERROR(("endpoint_close in endpoint_accept #2\n"));
                    OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_send_lock);
                    OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_recv_lock);
                    return false;
                }
                mca_btl_sctp_endpoint_event_init(btl_endpoint, sd);
                opal_event_add(&btl_endpoint->endpoint_recv_event, 0);
                mca_btl_sctp_endpoint_connected(btl_endpoint);
#if OPAL_ENABLE_DEBUG && WANT_PEER_DUMP
                mca_btl_sctp_endpoint_dump(btl_endpoint, "accepted");
#endif
                OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_send_lock);
                OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_recv_lock);
                return true;
            }
        }
        OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_send_lock);
        OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_recv_lock);
        return false;
    }

    else {

        mca_btl_sctp_addr_t* btl_addr;

        OPAL_THREAD_LOCK(&btl_endpoint->endpoint_recv_lock);
        OPAL_THREAD_LOCK(&btl_endpoint->endpoint_send_lock);
        if((btl_addr = btl_endpoint->endpoint_addr) != NULL) {


            mca_btl_sctp_endpoint_event_init(btl_endpoint, sd);
            opal_event_add(&btl_endpoint->endpoint_recv_event, 0);
#if OPAL_ENABLE_DEBUG && WANT_PEER_DUMP
            mca_btl_sctp_endpoint_dump(btl_endpoint, "accepted");
#endif
            OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_send_lock);
            OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_recv_lock);
            return true;
        }
        OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_send_lock);
        OPAL_THREAD_UNLOCK(&btl_endpoint->endpoint_recv_lock);
        return false;
    }
}
