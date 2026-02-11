wasp_string_append_code( wasp_string str, unsigned char ch ){
    char buf[4];
    memset( buf, '0', 3 );
    buf[3] = 0;
    int i = 3;

    do{
        buf[ --i ] = '0' + ch % 10;
    }while( ch /= 10 );

    wasp_string_append( str, buf, 3 );
}
