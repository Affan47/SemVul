us_webapp_static_buffer_destroy( us_webapp_t *self_ )
{
    us_webapp_static_buffer_t *self = (us_webapp_static_buffer_t *)self_;
    if ( self->m_owned_buffer )
    {
        if ( self->m_buffer )
        {
            self->m_buffer->destroy( self->m_buffer );
        }
    }
    us_delete( self->m_base.m_allocator, self->m_path );
    us_delete( self->m_base.m_allocator, self->m_content_type );
    us_webapp_destroy( self_ );
}
