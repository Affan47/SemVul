us_osc_msg_create( us_allocator_t *allocator, const char *address )
{
    us_osc_msg_t *r = 0;
    us_osc_msg_t *self = 0;
    self = us_new( allocator, us_osc_msg_t );
    if ( self && address )
    {
        int32_t address_len = (int32_t)strlen( address );
        self->m_allocator = allocator;
        self->m_address = (char *)allocator->alloc( allocator, address_len + 1, 1 );
        if ( self->m_address )
        {
            strcpy( self->m_address, address );
            self->destroy = us_osc_msg_destroy;
            self->append = us_osc_msg_append;
            self->flatten = us_osc_msg_flatten;
#if US_ENABLE_PRINTING
            self->print = us_osc_msg_print;
#endif
            self->m_first_element = 0;
            self->m_last_element = 0;
            self->m_next = 0;
            r = self;
        }
    }
    return r;
}
