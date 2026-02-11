add_xgrid( FL_OBJECT * ob )
{
    FLI_XYPLOT_SPEC *sp = ob->spec;
    int xr, i;
    int savels = flps_get_linestyle( );

    flps_linestyle( sp->grid_linestyle );

    for ( i = 0; sp->xgrid == FL_GRID_MINOR && i < sp->num_xminor; i++ )
    {
        xr = sp->xtic_minor[ i ];
        flps_line( xr, ym1, xr, ym2, ob->col2 );
    }

    for ( i = 0; i < sp->num_xmajor; i++ )
    {
        xr = sp->xtic_major[ i ];
        flps_line( xr, ym1, xr, ym2, ob->col2 );
    }

    flps_linestyle( savels );
}
