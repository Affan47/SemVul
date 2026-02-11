_sm_router_connect(sm_t sm) {
    log_write(sm->log, LOG_NOTICE, "attempting connection to router at %s, port=%d", sm->router_ip, sm->router_port);

    sm->fd = mio_connect(sm->mio, sm->router_port, sm->router_ip, NULL, sm_mio_callback, (void *) sm);
    if(sm->fd == NULL) {
        if(errno == ECONNREFUSED)
            sm_lost_router = 1;
        log_write(sm->log, LOG_NOTICE, "connection attempt to router failed: %s (%d)", MIO_STRERROR(MIO_ERROR), MIO_ERROR);
        return 1;
    }

    sm->router = sx_new(sm->sx_env, sm->fd->fd, sm_sx_callback, (void *) sm);
    sx_client_init(sm->router, 0, NULL, NULL, NULL, "1.0");

    return 0;
}
