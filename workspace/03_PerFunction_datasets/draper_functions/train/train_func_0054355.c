us_buffer_read_rounded_string( us_buffer_t *self, char *value, size_t result_max_len )
{
    bool r = false;
    r = us_buffer_read_string( self, value, result_max_len );
    if ( r )
    {

        size_t len = strlen( value );
        size_t skip = 3 - ( len & 3 );
        us_buffer_skip( self, skip );
    }
    return r;
}
