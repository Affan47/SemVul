us_http_request_header_create( us_allocator_t *allocator )
{
    us_http_request_header_t *self;
    self = us_new( allocator, us_http_request_header_t );
    if ( self )
    {
        self->m_allocator = allocator;
        self->destroy = us_http_request_header_destroy;
        self->m_items = us_http_header_item_list_create( allocator );
        self->m_method = 0;
        self->m_path = 0;
        self->m_version = 0;
        if ( self->m_items == 0 )
        {
            us_delete( allocator, self );
            self = 0;
        }
    }
    return self;
}
