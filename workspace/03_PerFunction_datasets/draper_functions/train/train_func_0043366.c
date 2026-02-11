us_getopt_destroy( us_getopt_t *self )
{
    us_getopt_option_list_t *cur = self->m_option_lists;
    if ( cur )
    {
        us_getopt_option_list_destroy( self, cur, self->m_allocator );
    }
    self->m_option_lists = 0;
}
