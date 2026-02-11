save_twheel_attrib( FILE      * fp,
                    FL_OBJECT * ob )
{
    FL_OBJECT *defobj;
    SuperSPEC *defsp,
              *sp;

    if ( ob->objclass != FL_THUMBWHEEL )
        return;


    defobj = fl_create_thumbwheel( ob->type, 0, 0, 0, 0, "" );

    defsp = get_superspec( defobj );
    sp = get_superspec( ob );

    if ( sp->min != defsp->min || sp->max != defsp->max )
        fprintf( fp, "    bounds: %g %g\n", sp->min, sp->max );

    if ( sp->prec != defsp->prec )
        fprintf( fp, "    precision: %d\n", sp->prec );

    if ( sp->val != defsp->val )
        fprintf( fp, "    value: %g\n", sp->val );

    if ( sp->ldelta != defsp->ldelta || sp->rdelta != defsp->rdelta )
        fprintf( fp, "    increment: %g %g\n", sp->ldelta, sp->rdelta );

    if ( sp->slsize != defsp->slsize )
        fprintf( fp, "    slsize: %.2f\n", sp->slsize );

    if ( sp->step != defsp->step )
        fprintf( fp, "    step: %g\n", sp->step );
}
