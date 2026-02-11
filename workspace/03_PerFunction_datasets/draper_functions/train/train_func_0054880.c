draw_square( FL_Coord x,
             FL_Coord y,
             FL_Coord w,
             FL_Coord h,
             int      angle  FL_UNUSED_ARG,
             FL_COLOR col )
{
    int s = ( 0.09 * w ) + 3;

    ShrinkBox( x, y, w, h, s );

    if ( w <= 1 )
        w = 2;

    if ( h <= 1 )
        h = 2;

    fl_rectbound( x, y, w - 1, h - 1, col );
}
