mca_btl_tcp_endpoint_complete_connect(mca_btl_base_endpoint_t* btl_endpoint)
{
    int so_error = 0;
    opal_socklen_t so_length = sizeof(so_error);
    struct sockaddr_storage endpoint_addr;

    mca_btl_tcp_proc_tosocks(btl_endpoint->endpoint_addr, &endpoint_addr);


    opal_event_del(&btl_endpoint->endpoint_send_event);


    if(getsockopt(btl_endpoint->endpoint_sd, SOL_SOCKET, SO_ERROR, (char *)&so_error, &so_length) < 0) {
        BTL_ERROR(("getsockopt() to %s failed: %s (%d)",
                   opal_net_get_hostname((struct sockaddr*) &endpoint_addr),
                   strerror(opal_socket_errno), opal_socket_errno));
        mca_btl_tcp_endpoint_close(btl_endpoint);
        return;
    }
    if(so_error == EINPROGRESS || so_error == EWOULDBLOCK) {
        opal_event_add(&btl_endpoint->endpoint_send_event, 0);
        return;
    }
    if(so_error != 0) {
        BTL_ERROR(("connect() to %s failed: %s (%d)",
                   opal_net_get_hostname((struct sockaddr*) &endpoint_addr),
                   strerror(so_error), so_error));
        mca_btl_tcp_endpoint_close(btl_endpoint);
        return;
    }

    if(mca_btl_tcp_endpoint_send_connect_ack(btl_endpoint) == OMPI_SUCCESS) {
        btl_endpoint->endpoint_state = MCA_BTL_TCP_CONNECT_ACK;
        opal_event_add(&btl_endpoint->endpoint_recv_event, 0);
    } else {
        btl_endpoint->endpoint_state = MCA_BTL_TCP_FAILED;
        mca_btl_tcp_endpoint_close(btl_endpoint);
    }
}
