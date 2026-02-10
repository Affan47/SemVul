us_reactor_destroy( us_reactor_t *self )
{
    while ( self->m_handlers )
    {
        self->remove_item( self, self->m_handlers );
    }
#if defined( US_REACTOR_USE_POLL )
    us_delete( self->m_allocator, self->m_poll_handlers );
    self->m_poll_handlers = 0;
#endif
}
