get_colors( Colormap   colormap,
            int      * red_lut,
            int      * green_lut,
            int      * blue_lut,
            int        map_len,
            int      * allocated )
{
    XColor xc;
    unsigned long *newpixels = 0;
    int npixels,
        i;

    *allocated = 0;

    if ( map_len <= 0 )
    {
        M_err( "get_colors", "bad map length %d\n", map_len );
        return 0;
    }

    if ( ! ( newpixels = fl_malloc( map_len * sizeof *newpixels ) ) )
    {
        M_err( "get_colors", "malloc failed while getting colors" );
        return 0;
    }

    xc.flags = DoRed | DoGreen | DoBlue;

    for ( npixels = i = 0; i < map_len; i++ )
    {
        xc.red   = ( red_lut[   i ] << 8 ) | 0xff;
        xc.green = ( green_lut[ i ] << 8 ) | 0xff;
        xc.blue  = ( blue_lut[  i ] << 8 ) | 0xff;
        if ( XAllocColor( fl_display, colormap, &xc ) )
            newpixels[ npixels++ ] = xc.pixel;
    }

    *allocated = npixels;
    return newpixels;
}
