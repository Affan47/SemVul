gray_to_mono( FL_IMAGE * im )
{
    unsigned short **outm = fl_get_matrix( im->h, im->w, sizeof **outm );
    unsigned short *in,
                   *out,
                   *end;
    int status = 0;

    if ( dither_threshold <= 0 )
        dither_threshold = ( 1 << FL_PCBITS ) / 2;

    if ( dither_method == FS_DITHER )
        status = fs_dither( im->gray, im->h, im->w, outm );
    else if ( dither_method == DITHER_THRESHOLD )
    {
        in = im->gray[ 0 ];
        for ( out = outm[ 0 ], end = in + im->w * im->h; in < end; )
            *out++ = *in++ >= dither_threshold;
    }

    if ( status >= 0 )
    {
        fl_free_matrix( im->ci );
        im->ci = outm;
        im->map_len = 2;
        flimage_getcolormap( im );

        im->red_lut[ 0 ] = im->green_lut[ 0 ] = im->blue_lut[ 0 ] = FL_PCMAX;
        im->red_lut[ 1 ] = im->green_lut[ 1 ] = im->blue_lut[ 1 ] = 0;
    }

    return status;
}
