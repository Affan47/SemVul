add_xtics( FL_OBJECT * ob )
{
    FLI_XYPLOT_SPEC *sp = ob->spec;
    float tic = sp->xtic;
    int xr,
        ticl = 6,
        yi,
        yf,
        i;
    char buf[ 80 ],
         *label,
         *p;

    if ( tic <= 0 )
        return;

    yi = ym1;
    yf = yi - ticl / 2;

    for ( i = 0; i < sp->num_xminor; i++ )
    {
        xr = sp->xtic_minor[ i ];
        flps_line( xr, yi, xr, yf, ob->col2 );
    }

    yi = ym1;
    yf = yi - ticl;

    for ( i = 0; i < sp->num_xmajor; i++ )
    {
        xr = sp->xtic_major[ i ];
        flps_line( xr, yi, xr, yf, ob->col2 );

        if ( ! sp->axtic[ 0 ] )
            fli_xyplot_nice_label( tic, sp->xminor,
                                   sp->xmajor_val[ i ], label = buf );
        else
        {
            if ( ( p = strchr( sp->axtic[ i ], '@' ) ) )
            {
                label = strcpy( buf, sp->axtic[ i ] );
                label[ p - sp->axtic[ i ] ] = '\0';
            }
            else
                label = sp->axtic[ i ];
        }

        flps_draw_text( FL_ALIGN_TOP, xr, ym1 - ticl + 1, 0, 0,
                        ob->col2, sp->lstyle, sp->lsize, label );
    }
}
