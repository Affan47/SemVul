us_getopt_escape( char *dest, size_t dest_len, const char *str, size_t str_len )
{
    bool r = true;
    size_t i;
    size_t dp = 0;
    for ( i = 0; i < str_len; ++i )
    {
        char c = str[i];
        if ( dp > dest_len - 4 )
        {
            r = false;
            break;
        }
        switch ( c )
        {
        case '"':
            dest[dp++] = '\\';
            dest[dp++] = '"';
            break;
        case '\r':
            dest[dp++] = '\\';
            dest[dp++] = 'r';
            break;
        case '\n':
            dest[dp++] = '\\';
            dest[dp++] = 'n';
            break;
        case '\t':
            dest[dp++] = '\\';
            dest[dp++] = 't';
            break;
        default:
            if ( isprint( c ) )
            {
                dest[dp++] = c;
            }
            else
            {
                US_DEFAULT_SNPRINTF( &dest[dp], 3, "\\%2x", c );
                dp += 3;
            }
            break;
        }
    }
    if ( r )
    {
        dest[dp] = '\0';
    }
    else
    {
        dest[0] = '\0';
    }
    return r;
}
