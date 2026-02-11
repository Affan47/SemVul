fl_rectangle( int      fill,
              FL_Coord x,
              FL_Coord y,
              FL_Coord w,
              FL_Coord h,
              FL_COLOR col )
{
    int bw = fli_dithered( fl_vmode ) && fli_mono_dither( col );
    GC gc = flx->gc;
    int ( * draw_as )( Display *,
                       Drawable,
                       GC,
                       int,
                       int,
                       unsigned int,
                       unsigned int );

    if ( flx->win == None || w <= 0 || h <= 0 )
        return;

    fli_canonicalize_rect( &x, &y, &w, &h );

    draw_as = fill ? XFillRectangle : XDrawRectangle;

    if ( bw && fill )
    {
        fli_set_current_gc( fli_whitegc );
        draw_as( flx->display, flx->win, flx->gc, x, y, w, h );
        fli_set_current_gc( dithered_gc );
    }


    fl_color( bw ? FL_BLACK : col );
    draw_as( flx->display, flx->win, flx->gc, x, y, w, h );

    if ( bw )
        fli_set_current_gc( gc );
}
