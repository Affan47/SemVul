fl_getmcolor( FL_COLOR i,
              int *    r,
              int *    g,
              int *    b )
{
    XColor exact;

    if ( ( exact.pixel = fl_get_pixel( i ) ) >= max_server_cols )
    {
        *r = *g = *b = 0;
        return ( unsigned long ) -1;
    }

    XQueryColor( flx->display, fli_map( fl_vmode ), &exact );

    *r = ( exact.red   >> 8 ) & 0xff;
    *g = ( exact.green >> 8 ) & 0xff;
    *b = ( exact.blue  >> 8 ) & 0xff;

    return exact.pixel;
}
