ps_draw_text( int          align,
              float        x,
              float        y,
              float        w,
              float        h,
              long         col,
              int          style,
              int          size,
              const char * str)
{
    int special = FL_INVALID_STYLE;

    if ( ! str || ! *str )
        return;

    if ( *str == '@' )
    {
        ps_draw_symbol( str, x, y, w, h, col );
        return;
    }

    if ( special_style( style ) )
    {
        special = ( style / FL_SHADOW_STYLE ) * FL_SHADOW_STYLE;
        style %= FL_SHADOW_STYLE;
    }

    if ( special == FL_SHADOW_STYLE )
        D( x + 2, y - 2, FL_BOTTOM_BCOL );
    else if ( special == FL_ENGRAVED_STYLE )
    {
        D( x - 1, y,     FL_RIGHT_BCOL );
        D( x,     y + 1, FL_RIGHT_BCOL );
        D( x - 1, y + 1, FL_RIGHT_BCOL );
        D( x + 1, y,     FL_LEFT_BCOL );
        D( x,     y - 1, FL_LEFT_BCOL );
        D( x + 1, y - 1, FL_LEFT_BCOL );
    }
    else if ( special == FL_EMBOSSED_STYLE )
    {
        D( x - 1, y,     FL_TOP_BCOL );
        D( x,     y + 1, FL_TOP_BCOL );
        D( x - 1, y + 1, FL_TOP_BCOL );
        D( x + 1, y,     FL_RIGHT_BCOL );
        D( x,     y - 1, FL_RIGHT_BCOL );
        D( x + 1, y - 1, FL_RIGHT_BCOL );
    }

    ps_drw_text( align, x, y, w, h, col, style, size, str );
}
