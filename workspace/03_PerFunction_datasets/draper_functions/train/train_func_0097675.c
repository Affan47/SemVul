us_reactor_handler_tcp_client_init( us_reactor_handler_t *self_,
                                         us_allocator_t *allocator,
                                         int fd,
                                         void *extra,
                                         int queue_buf_size,
                                         const char *client_host,
                                         const char *client_port,
                                         bool keep_open )
{
    us_reactor_handler_tcp_client_t *self = (us_reactor_handler_tcp_client_t *)self_;
    bool r = true;
    r &= us_reactor_handler_tcp_init( self_, allocator, fd, extra, queue_buf_size );
    if ( r )
    {
        self->m_client_host = us_strdup( allocator, client_host );
        self->m_client_port = us_strdup( allocator, client_port );
        self->m_is_connected = false;
        if ( keep_open )
        {
            self->m_keep_open = true;
            self->m_try_once = false;
        }
        else
        {
            self->m_keep_open = false;
            self->m_try_once = true;
        }
        self->m_base.m_base.destroy = us_reactor_handler_tcp_client_destroy;
        self->m_base.tick = us_reactor_handler_tcp_client_tick;
        self->m_base.closed = us_reactor_handler_tcp_client_closed;
    }
    return r;
}
