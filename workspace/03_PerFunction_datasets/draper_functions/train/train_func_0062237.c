us_simple_allocator_alloc( us_allocator_t *self_, int32_t length, int32_t count )
{
    us_simple_allocator_t *self = (us_simple_allocator_t *)self_;
    void *result = 0;

    int32_t total_size_to_allocate = us_round_size( length * count );
    if ( ( self->m_current_position + total_size_to_allocate ) <= ( self->m_raw_memory_length ) )
    {
        result = ( (char *)self->m_raw_memory ) + self->m_current_position;
        self->m_current_position += total_size_to_allocate;
    }
    return result;
}
