fl_lines( FL_POINT * xp,
          int        n,
          FL_COLOR   col )
{
    if ( flx->win == None  || n <= 0 )
        return;

    fl_color( col );


    if ( fli_context->ext_request_size >= n )
        XDrawLines( flx->display, flx->win, flx->gc, xp, n, CoordModeOrigin );
    else
    {
        int req = fli_context->ext_request_size;
        int i,
            nchunks = ( n + ( n / req ) ) / req,
            left;
        FL_POINT *p = xp;

        for ( i = 0; i < nchunks; i++, p += req - 1 )
            XDrawLines( flx->display, flx->win, flx->gc, p, req,
                        CoordModeOrigin );

        left = xp + n - p;

        if ( left )
        {
            if ( left == 1 )
            {
                p--;
                left++;
            }

            XDrawLines( flx->display, flx->win, flx->gc, p, left,
                        CoordModeOrigin );
        }
    }
}
