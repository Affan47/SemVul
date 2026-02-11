ps_draw_text_beside( int          align,
                     float        x,
                     float        y,
                     float        w,
                     float        h,
                     long         col,
                     int          style,
                     int          size,
                     const char * str )
{
    int newa, newx, newy;

    if ( ! str || ! *str )
        return;

    align &= ~FL_ALIGN_INSIDE;
#if 1
    fl_get_outside_align( align, x, y, w, h, &newa, &newx, &newy );
    ps_draw_text( newa, newx, newy, w, h, col, style, size, str );
#else
    if ( align == FL_ALIGN_LEFT )
        ps_draw_text( FL_ALIGN_RIGHT, x - h, y, h, h, col, style, size, str );
    else if ( align == FL_ALIGN_RIGHT )
        ps_draw_text( FL_ALIGN_LEFT, x + w, y, h, h, col, style, size, str );
    else if ( align == FL_ALIGN_TOP )
        ps_draw_text( FL_ALIGN_BOTTOM, x, y + h, w, h, col, style, size, str );
    else if ( align == FL_ALIGN_BOTTOM )
        ps_draw_text( FL_ALIGN_TOP, x, y - h, w, h, col, style, size, str );
    else
        ps_draw_text( FL_ALIGN_CENTER, x, y, w, h, col, style, size, str );
#endif
}
