us_reactor_handler_tcp_tick( us_reactor_handler_t *self_ )
{
    bool r = true;
    us_reactor_handler_tcp_t *self = (us_reactor_handler_tcp_t *)self_;
    size_t incoming_count = us_buffer_contig_writable_count( &self->m_incoming_queue );
    bool outgoing_available = us_buffer_can_read_byte( &self->m_outgoing_queue );
    us_reactor_log_tracepoint();

    if ( incoming_count > 0 )
    {
        self->m_base.m_wake_on_readable = true;
    }
    else
    {
        self->m_base.m_wake_on_readable = false;
    }


    if ( outgoing_available || ( !outgoing_available && self->writable ) )
    {
        self->m_base.m_wake_on_writable = true;
    }
    else
    {
        self->m_base.m_wake_on_writable = false;
    }
    if ( self->tick )
        r = self->tick( self );
    us_reactor_log_trace(
        "fd %d WOR: %d WOW: %d", self->m_base.m_fd, self->m_base.m_wake_on_readable, self->m_base.m_wake_on_writable );
    return r;
}
