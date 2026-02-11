mca_btl_sctp_endpoint_event_init(mca_btl_base_endpoint_t* btl_endpoint, int sd)
{
    if(mca_btl_sctp_component.sctp_if_11) {


#if MCA_BTL_SCTP_ENDPOINT_CACHE
        btl_endpoint->endpoint_cache     = (char*)malloc(mca_btl_sctp_component.sctp_endpoint_cache);
        btl_endpoint->endpoint_cache_pos = btl_endpoint->endpoint_cache;
#endif

        opal_event_set(opal_event_base, &btl_endpoint->endpoint_recv_event,
                btl_endpoint->endpoint_sd,
                OPAL_EV_READ|OPAL_EV_PERSIST,
                mca_btl_sctp_endpoint_recv_handler,
                btl_endpoint );
        opal_event_set(opal_event_base, &btl_endpoint->endpoint_send_event,
                btl_endpoint->endpoint_sd,
               OPAL_EV_WRITE|OPAL_EV_PERSIST,
                mca_btl_sctp_endpoint_send_handler,
                btl_endpoint);
    }

    else {

        if(0 == btl_endpoint->endpoint_has_initialized) {
            btl_endpoint->endpoint_has_initialized++;

            btl_endpoint->endpoint_sd = mca_btl_sctp_component.sctp_listen_sd;

#if MCA_BTL_SCTP_ENDPOINT_CACHE
            btl_endpoint->endpoint_cache     = (char*)malloc(mca_btl_sctp_component.sctp_endpoint_cache);
            btl_endpoint->endpoint_cache_pos = btl_endpoint->endpoint_cache;
#endif

            opal_event_set(opal_event_base, &btl_endpoint->endpoint_recv_event,
                            btl_endpoint->endpoint_sd,
                            OPAL_EV_READ|OPAL_EV_PERSIST,
                            mca_btl_sctp_recv_handler,
                            btl_endpoint );
            opal_event_set(opal_event_base, &btl_endpoint->endpoint_send_event,
                            btl_endpoint->endpoint_sd,
                            OPAL_EV_WRITE|OPAL_EV_PERSIST,
                            mca_btl_sctp_endpoint_send_handler,
                            btl_endpoint);
        }
    }
}
