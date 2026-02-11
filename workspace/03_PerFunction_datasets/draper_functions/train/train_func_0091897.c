fl_polygon( int        fill,
            FL_POINT * xp,
            int        n,
            FL_COLOR   col )
{
    int bw = fli_dithered( fl_vmode ) && fli_mono_dither( col );
    GC gc = flx->gc;

    if ( flx->win == None || n <= 0 )
        return;

    if ( bw )
    {
        flx->gc = dithered_gc;
        fl_color( FL_WHITE );
        if ( fill )
            XFillPolygon( flx->display, flx->win, flx->gc, xp, n,
                          Nonconvex, CoordModeOrigin );
        else
        {
            xp[ n ].x = xp[ 0 ].x;
            xp[ n ].y = xp[ 0 ].y;
            n++;
            XDrawLines( flx->display, flx->win, flx->gc, xp, n,
                        CoordModeOrigin );
        }
    }

    fl_color( bw ? FL_BLACK : col );

    if ( fill )
        XFillPolygon( flx->display, flx->win, flx->gc, xp, n,
                      Nonconvex, CoordModeOrigin );
    else
    {
        xp[ n ].x = xp[ 0 ].x;
        xp[ n ].y = xp[ 0 ].y;
        n++;
        XDrawLines( flx->display, flx->win, flx->gc, xp, n, CoordModeOrigin );
    }

    if ( bw )
        flx->gc = gc;
}
