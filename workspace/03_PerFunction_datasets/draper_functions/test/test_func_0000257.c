us_parse_hexoctet( uint8_t *val, const char *buf, size_t buf_len, size_t *buf_pos )
{
    bool r = true;
    uint8_t high = 0;
    uint8_t low = 0;
    r &= us_parse_hexdig( &high, buf, buf_len, buf_pos );
    r &= us_parse_hexdig( &low, buf, buf_len, buf_pos );
    if ( r )
    {
        *val = ( high << 4 ) + low;
    }
    return r;
}
