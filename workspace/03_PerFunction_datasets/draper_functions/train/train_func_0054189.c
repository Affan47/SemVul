fl_insert_xyplot_data( FL_OBJECT * ob,
                       int         id,
                       int         n,
                       double      x,
                       double      y )
{
    FLI_XYPLOT_SPEC *sp = ob->spec;
    float *xx,
          *yy;

    if ( id < 0 || id > sp->maxoverlay )
        return;

    if ( n < -1 )
        n = -1;
    else if ( n >= sp->n[ id ] )
        n = sp->n[ id ] - 1;

    n = n + 1;
    sp->n[ id ] += 1;

    if ( n == sp->n[ id ] - 1 )
    {
        sp->x[ id ] = fl_realloc( sp->x[ id ],
                                  sp->n[ id ] * sizeof **sp->x );
        sp->y[ id ] = fl_realloc( sp->y[ id ],
                                  sp->n[ id ] * sizeof **sp->y );
        sp->x[ id ][ n ] = x;
        sp->y[ id ][ n ] = y;
    }
    else
    {
        xx = fl_malloc( sp->n[ id ] * sizeof *xx );
        yy = fl_malloc( sp->n[ id ] * sizeof *yy );

        if ( n )
        {
            memcpy( xx, sp->x[ id ], n * sizeof *xx );
            memcpy( yy, sp->y[ id ], n * sizeof *yy );
        }

        xx[ n ] = x;
        yy[ n ] = y;

        memcpy( xx + n + 1, sp->x[ id ] + n,
                ( sp->n[ id ] - n - 1 ) * sizeof *xx );
        memcpy( yy + n + 1, sp->y[ id ] + n,
                ( sp->n[ id ] - n - 1 ) * sizeof *yy );

        fl_free( sp->x[ id ] );
        fl_free( sp->y[ id ] );

        sp->x[ id ] = xx;
        sp->y[ id ] = yy;
    }

    extend_screen_data( sp, sp->n[ id ] );

    fl_redraw_object( ob );
}
