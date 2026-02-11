mca_btl_sctp_endpoint_start_connect(mca_btl_base_endpoint_t* btl_endpoint)
{
    if(mca_btl_sctp_component.sctp_if_11) {

        int rc;
        struct sockaddr_in endpoint_addr;

        btl_endpoint->endpoint_sd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
        if (btl_endpoint->endpoint_sd < 0) {
            btl_endpoint->endpoint_retries++;
            return OMPI_ERR_UNREACH;
        }


        if(bind(btl_endpoint->endpoint_sd, (struct sockaddr *)
                &btl_endpoint->endpoint_btl->sctp_ifaddr,
                sizeof(struct sockaddr_in)) < 0) {
                return OMPI_ERR_FATAL;
        }


        if((rc = mca_btl_sctp_set_socket_options(btl_endpoint->endpoint_sd)) != OMPI_SUCCESS) {
            return OMPI_ERR_FATAL;
        }


        mca_btl_sctp_endpoint_event_init(btl_endpoint, btl_endpoint->endpoint_sd);


	memset(&endpoint_addr, 0, sizeof(endpoint_addr));
        endpoint_addr.sin_family = AF_INET;
        endpoint_addr.sin_addr = btl_endpoint->endpoint_addr->addr_inet;
        endpoint_addr.sin_port = btl_endpoint->endpoint_addr->addr_port;
#ifdef FREEBSD
        endpoint_addr.sin_len = sizeof(struct sockaddr);
#endif
        if(connect(btl_endpoint->endpoint_sd, (struct sockaddr*)&endpoint_addr,
                   sizeof(endpoint_addr)) < 0)
        {

            if(opal_socket_errno == EINPROGRESS ||
               opal_socket_errno == EWOULDBLOCK)
            {
                btl_endpoint->endpoint_state = MCA_BTL_SCTP_CONNECTING;
                opal_event_add(&btl_endpoint->endpoint_send_event, 0);
                return OMPI_SUCCESS;
            }
            SCTP_BTL_ERROR(("endpoint_close in start_connect #1\n"));
            mca_btl_sctp_endpoint_close(btl_endpoint);
            btl_endpoint->endpoint_retries++;
            return OMPI_ERR_UNREACH;
        }


        if((rc = mca_btl_sctp_endpoint_send_connect_ack(btl_endpoint)) == OMPI_SUCCESS) {
            btl_endpoint->endpoint_state = MCA_BTL_SCTP_CONNECT_ACK;
            opal_event_add(&btl_endpoint->endpoint_recv_event, 0);
        } else {
            SCTP_BTL_ERROR(("endpoint_close in start_connect #2\n"));
            mca_btl_sctp_endpoint_close(btl_endpoint);
        }
        return rc;
    }

    else {

        int rc;
        struct sockaddr_in endpoint_addr;


        mca_btl_sctp_endpoint_event_init(btl_endpoint, btl_endpoint->endpoint_sd);
        if (btl_endpoint->endpoint_sd < 0) {
            btl_endpoint->endpoint_retries++;
            return OMPI_ERR_UNREACH;
        }

        endpoint_addr = mca_btl_sctp_utils_sockaddr_from_endpoint(btl_endpoint);


        if((rc = mca_btl_sctp_endpoint_send_connect_ack(btl_endpoint)) == OMPI_SUCCESS) {

            mca_btl_sctp_endpoint_connected(btl_endpoint);

        } else {
            SCTP_BTL_ERROR(("endpoint_close in start_connect #3\n"));
            mca_btl_sctp_endpoint_close(btl_endpoint);
        }
        return rc;
    }
}
