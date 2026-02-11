us_buffer_create( us_allocator_t *allocator, size_t max_length )
{
    us_buffer_t *r = 0;
    us_buffer_t *self;
    self = us_new( allocator, us_buffer_t );
    if ( self )
    {
        r = us_buffer_init( self, allocator, allocator->alloc( allocator, (int32_t)max_length, 1 ), max_length );
    }
    return r;
}
