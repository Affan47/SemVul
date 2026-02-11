XBM_description( FL_IMAGE * im )
{
    char tmpstr[ 256 ];
    int w = -1,
        h = -1,
        no_size = 1,
        c;

    while ( no_size && fgets( tmpstr, sizeof tmpstr, im->fpin ) )
    {
        if ( sscanf( tmpstr, "#define %*s %d", &c ) == 1 )
        {
            if ( strstr( tmpstr, "_width" ) )
                w = c;
            else if ( strstr( tmpstr, "_height" ) )
                h = c;
            no_size = w < 1 || h < 1;
        }
    }

    if ( no_size )
    {
        im->error_message( im, "can't get xbm size" );
        return -1;
    }

    im->w = w;
    im->h = h;

    im->map_len = 2;


    while ( ( h = getc( im->fpin ) ) != EOF && h != '{' )
         ;

    return h == EOF ? EOF : 0;
}
