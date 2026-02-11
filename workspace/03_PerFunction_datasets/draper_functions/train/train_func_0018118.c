us_webapp_fs_create( us_allocator_t *allocator,
                                  us_webapp_file_ext_mime_map_t *ext_map,
                                  const char *web_path_prefix,
                                  const char *filesystem_path )
{
    us_webapp_fs_t *self = us_new( allocator, us_webapp_fs_t );
    if ( self )
    {
        if ( !us_webapp_init( &self->m_base, allocator ) )
        {
            us_webapp_destroy( &self->m_base );
            self = 0;
        }
    }
    if ( self )
    {
        self->m_base.destroy = us_webapp_fs_destroy;
        self->m_base.dispatch = us_webapp_fs_dispatch;
        self->m_base.path_match = us_webapp_fs_path_match;
        self->m_web_path_prefix_len = (int)strlen( web_path_prefix );
        self->m_filesystem_path = us_strdup( allocator, filesystem_path );
        self->m_web_path_prefix = us_strdup( allocator, web_path_prefix );
        if ( ext_map )
        {
            self->m_ext_map = ext_map;
        }
        else
        {
            self->m_ext_map = us_webapp_fs_default_ext_map;
        }
        if ( self->m_filesystem_path == 0 || self->m_web_path_prefix == 0 )
        {
            self->m_base.destroy( &self->m_base );
            self = 0;
        }
    }
    return &self->m_base;
}
