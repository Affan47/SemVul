us_webapp_director_dispatch( us_webapp_director_t *self,
                                 const us_http_request_header_t *request_header,
                                 const us_buffer_t *request_content,
                                 us_http_response_header_t *response_header,
                                 us_buffer_t *response_content )
{
    int http_code = -1;
    us_webapp_t *cur = self->m_apps;

    while ( cur && http_code == -1 )
    {
        if ( cur->path_match( cur, request_header->m_path ) )
        {
            http_code = cur->dispatch( cur, request_header, request_content, response_header, response_content );
        }
        if ( http_code == -1 )
        {
            cur = cur->m_next;
        }
    }

    if ( http_code == -1 || http_code == 404 )
    {
        if ( self->m_404_app )
        {
            http_code = self->m_404_app->dispatch(
                self->m_404_app, request_header, request_content, response_header, response_content );
        }
        else
        {
            static const char default_404_type[] = "text/html; charset=utf-8";
            static const char default_404[]
                = "<html><head><title>Error 404: Not Found</title></head><body><h1>Error 404</h1><p>Not "
                  "Found</p></body></html>";
            us_http_response_header_init_error( response_header, 404, default_404_type, sizeof( default_404 ) );
            us_buffer_append_string( response_content, default_404 );
        }
    }

    if ( http_code == -1 )
    {
        http_code = 500;
        us_http_response_header_init_error( response_header, http_code, 0, 0 );
    }
    return http_code;
}
