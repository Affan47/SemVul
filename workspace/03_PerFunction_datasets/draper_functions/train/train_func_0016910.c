write_descriptor( FL_IMAGE * im )
{
    unsigned char buf[ 10 ];
    FILE *ffp = im->fpout;

    if ( im->app_background >= 0 )
    {
        int tran = flimage_get_closest_color_from_map( im, im->app_background );
        size_t dummy;

        buf[ 0 ] = GIFEXT_GC;
        buf[ 1 ] = 4;
        buf[ 2 ] = 0x1;
        buf[ 3 ] = 0;
        buf[ 4 ] = 0;
        buf[ 5 ] = tran;
        buf[ 6 ] = 0;
        putc( EXTENSION, ffp );
        dummy = fwrite( buf, 1, 7, ffp );
    }


    buf[ 0 ] = IMAGESEP;
    buf[ 1 ] = buf[ 2 ] = buf[ 3 ] = buf[ 4 ] = 0;
    if ( Badfwrite( buf, 1, 5, ffp ) )
        return -1;


    fli_fput2LSBF( im->w, ffp );
    fli_fput2LSBF( im->h, ffp );


    putc( interlace ? 0x40 : 0, ffp );
    return 0;
}
