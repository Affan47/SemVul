mca_btl_tcp_component_accept_handler( int incoming_sd,
                                                  short ignored,
                                                  void* unused )
{
    while(true) {
#if OPAL_ENABLE_IPV6
        struct sockaddr_in6 addr;
#else
        struct sockaddr_in addr;
#endif
        opal_socklen_t addrlen = sizeof(addr);

        mca_btl_tcp_event_t *event;
        int sd = accept(incoming_sd, (struct sockaddr*)&addr, &addrlen);
        if(sd < 0) {
            if(opal_socket_errno == EINTR)
                continue;
            if(opal_socket_errno != EAGAIN && opal_socket_errno != EWOULDBLOCK)
                BTL_ERROR(("accept() failed: %s (%d).",
                           strerror(opal_socket_errno), opal_socket_errno));
            return;
        }
        mca_btl_tcp_set_socket_options(sd);


        event = OBJ_NEW(mca_btl_tcp_event_t);
        opal_event_set(opal_event_base, &event->event, sd, OPAL_EV_READ, mca_btl_tcp_component_recv_handler, event);
        opal_event_add(&event->event, 0);
    }
}
