us_webapp_diag_dispatch( us_webapp_t *US_UNUSED( self ),
                             const us_http_request_header_t *request_header,
                             const us_buffer_t *request_content,
                             us_http_response_header_t *response_header,
                             us_buffer_t *response_content )
{
    us_http_header_item_t *item = 0;
    us_buffer_append_string( response_content, "Request Info\r\nMethod='" );
    us_buffer_append_string( response_content, request_header->m_method );
    us_buffer_append_string( response_content, "'\r\nPath='" );
    us_buffer_append_string( response_content, request_header->m_path );
    us_buffer_append_string( response_content, "'\r\nVersion='" );
    us_buffer_append_string( response_content, request_header->m_version );
    us_buffer_append_string( response_content, "'\r\n\r\n" );
    item = request_header->m_items->m_first;
    while ( item )
    {
        us_buffer_append_string( response_content, item->m_key );
        us_buffer_append_string( response_content, ": " );
        us_buffer_append_string( response_content, item->m_value );
        us_buffer_append_string( response_content, "\r\n" );
        item = item->m_next;
    }
    us_buffer_append_string( response_content, "\r\nContent is:\r\n" );
    us_buffer_write_buffer( response_content, request_content );
    response_header->m_code = 200;
    if ( !us_http_response_header_set_content_type( response_header, "text/plain" )
         || !us_http_response_header_set_content_length( response_header, (int)us_buffer_readable_count( response_content ) )
         || !us_http_response_header_set_connection_close( response_header ) )
    {
        return -1;
    }
    return response_header->m_code;
}
