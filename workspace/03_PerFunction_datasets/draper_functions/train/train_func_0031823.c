us_webapp_json_reply( us_http_response_header_t *header, us_buffer_t *buf, const us_json_t *m )
{
    bool r = true;
    r &= us_json_flatten_to_buffer( m, buf );
    r &= us_http_response_header_init_ok( header, 200, "application/json", (int)us_buffer_readable_count( buf ), true );
    r &= us_http_response_header_set_no_cache( header );
    if ( r )
        return header->m_code;
    else
        return 500;
}
