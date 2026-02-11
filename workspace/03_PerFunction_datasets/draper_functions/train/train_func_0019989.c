us_osc_sender_tcp_can_send( us_osc_sender_t *self_ )
{
    us_osc_sender_tcp_t *self = (us_osc_sender_tcp_t *)self_;
    bool r;
    if ( us_buffer_writable_count( &self->m_handler->m_outgoing_queue ) > self->m_max_size )
    {
        r = true;
    }
    else
    {
        r = false;
    }
    return r;
}
