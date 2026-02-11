emit_twheel_code( FILE      * fp,
                  FL_OBJECT * ob )
{
    FL_OBJECT *defobj;
    SuperSPEC *sp,
              *defsp;

    if ( ob->objclass != FL_THUMBWHEEL )
        return;


    defobj = fl_create_thumbwheel( ob->type, 0, 0, 0, 0, "" );

    defsp = get_superspec( defobj );
    sp = get_superspec( ob );

    if ( sp->prec != defsp->prec )
        fprintf( fp, "    fl_set_thumbwheel_precision( obj, %d );\n",
                 sp->prec );

    if ( sp->min != defsp->min || sp->max != defsp->max )
        fprintf( fp, "    fl_set_thumbwheel_bounds( obj, %g, %g );\n",
                 sp->min, sp->max );

    if ( sp->val != defsp->val )
        fprintf( fp, "    fl_set_thumbwheel_value( obj, %g );\n", sp->val );

    if ( sp->step != defsp->step )
        fprintf( fp, "    fl_set_thumbwheel_step( obj, %g );\n", sp->step );
}
