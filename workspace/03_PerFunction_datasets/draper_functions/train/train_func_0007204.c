get_all_colors( FL_IMAGE      * im,
                unsigned long   newpix[ ],
                int           * npix,
                XColor          xc[ ] )
{
    int i,
        max_colors = 1 << im->depth,
        n;

    for ( i = n = *npix = 0; i < im->map_len; i++ )
    {
        xc[ i ].flags = DoRed | DoGreen | DoBlue;
        xc[ i ].red   = ( im->red_lut[   i ] << 8 ) | 0xff;
        xc[ i ].green = ( im->green_lut[ i ] << 8 ) | 0xff;
        xc[ i ].blue  = ( im->blue_lut[  i ] << 8 ) | 0xff;

        if ( XAllocColor( im->xdisplay, im->xcolormap, xc + i ) )
            newpix[ n++ ] = xc[ i ].pixel;
        else
            xc[ i ].pixel = FL_NoColor;
    }

    *npix = n;

    if ( n < im->map_len )
    {
        XColor *mapentry = fl_malloc( max_colors * sizeof *mapentry );

        if ( ! mapentry )
        {
            M_err( "get_all_colors", "malloc failure(%d entries)", max_colors );
            return;
        }

        for ( i = 0; i < max_colors; i++ )
            mapentry[ i ].pixel = i;

        XQueryColors( im->xdisplay, im->xcolormap, mapentry, max_colors );

        for ( i = 0; i < im->map_len; i++ )
            if ( xc[ i ].pixel == FL_NoColor )
                fli_find_closest_color( xc[ i ].red   >> 8,
                                        xc[ i ].green >> 8,
                                        xc[ i ].blue  >> 8,
                                        mapentry, max_colors,
                                        &xc[ i ].pixel );

        fl_free( mapentry );
    }
}
