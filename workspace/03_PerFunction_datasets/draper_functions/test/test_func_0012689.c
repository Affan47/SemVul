flps_color( FL_COLOR color )
{
    int r = 0,
        g = 0,
        b = 0;

    if ( color == FL_NoColor )
        return;

    if ( flps->isRGBColor )
        FL_UNPACK( color, r, g, b );
    else
        flps_query_imap( color, &r, &g, &b );

    if ( ( FL_COLOR ) FL_PACK( r, g, b ) != flps->cur_color )
        flps_rgbcolor( r, g, b );
}
