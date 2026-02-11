fli_xyplot_interpolate( FL_OBJECT * ob,
                        int         id,
                        int         n1,
                        int         n2 )
{
    FLI_XYPLOT_SPEC *sp = ob->spec;
    int newn;
    float *x = sp->x[ id ],
          *y = sp->y[ id ];


    newn = 1.01 + ( x[ n2 - 1 ] - x[ n1 ] ) / sp->grid[ id ];


    if ( newn > 5000 )
    {
        M_err( "fli_xyplot_interpolate",
               "interpolating %d points, exceeds screen res", newn );
        return -1;
    }

    if ( newn > sp->nxpi )
    {
        sp->xpi--;
        sp->xpi = fl_realloc( sp->xpi, ( newn + 3 ) * sizeof *sp->xpi );
        sp->xpi++;
        sp->nxpi = newn;
    }

    if ( newn > sp->ninterpol )
    {
        sp->wx = fl_realloc( sp->wx, newn * sizeof *sp->wx );
        sp->wy = fl_realloc( sp->wy, newn * sizeof *sp->wy );

        if ( ! sp->wx || ! sp->wy )
        {
            if ( sp->wx )
                fl_realloc( sp->wx, sizeof *sp->wx );
            M_err( "fli_xyplot_interpolate",
                   "Can't allocate memory for %d points", newn );
            return -1;
        }
        sp->ninterpol = newn;
    }

    if ( fl_interpolate( x + n1, y + n1, n2 - n1,
                         sp->wx, sp->wy, sp->grid[ id ],
                         sp->interpolate[ id ] ) != newn )
    {
        M_err( "fli_xyplot_interpolate",
               "An error has occured while interpolating" );
        return -1;
    }

    return newn;
}
