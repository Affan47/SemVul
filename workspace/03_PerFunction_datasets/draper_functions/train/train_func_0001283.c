sfip_convert_ip_text_to_binary( const int family, char *ip, void *dst)
{
    char *my_ip;

    my_ip = ip;

    if( my_ip == NULL )
        return( SFIP_FAILURE );


    if( family == AF_INET ) {
        char chr;
        bool new_octet;

        new_octet = true;
        while( (chr = *my_ip++) != '\0') {


        if( new_octet && (chr == '0') && isdigit(*my_ip))
            return( SFIP_INET_PARSE_ERR );


        new_octet = (chr == '.');
        }
    }

    if( inet_pton(family, ip, dst) < 1 )
        return( SFIP_INET_PARSE_ERR );

    return( SFIP_SUCCESS );
}
