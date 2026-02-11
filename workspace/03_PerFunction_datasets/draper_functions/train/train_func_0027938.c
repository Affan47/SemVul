emit_spinner_code( FILE      * fp,
                   FL_OBJECT * obj )
{
    FL_OBJECT *defobj;
    SuperSPEC *spec,
              *defspec;

    if ( obj->objclass != FL_SPINNER )
        return;


    defobj = fl_create_spinner( obj->type, 0, 0, 0, 0, "" );

    defspec = get_superspec( defobj );
    spec = get_superspec( obj );

    if ( spec->prec != defspec->prec )
        fprintf( fp, "    fl_set_spinner_precision( obj, %d );\n",
                 spec->prec );

    if ( spec->dmin != defspec->dmin || spec->dmax != defspec->dmax )
        fprintf( fp, "    fl_set_spinner_bounds( obj, %.*f, %.*f );\n",
                 spec->prec, spec->dmin, spec->prec, spec->dmax );

    if ( spec->dval != defspec->dval )
        fprintf( fp, "    fl_set_spinner_value( obj, %.*f );\n",
                 spec->prec, spec->dval );

    if ( spec->dstep != defspec->dstep )
        fprintf( fp, "    fl_set_spinner_step( obj, %.*f );\n",
                 spec->prec, spec->dstep );

    if ( obj->lsize != defobj->lsize )
        fprintf( fp, "    fl_set_object_lsize( fl_get_spinner_input( obj ), "
                 "%s );\n", lsize_name( obj->lsize ) );

    if ( obj->lstyle != defobj->lstyle )
        fprintf( fp, "    fl_set_object_lstyle( fl_get_spinner_input( obj ), "
                 "%s );\n", style_name( obj->lstyle ) );

    if ( obj->col1 != defobj->col1 || obj->col2 != defobj->col2 )
        fprintf( fp, "    fl_set_object_color( fl_get_spinner_input( obj ), "
                 "%s, %s );\n", fli_query_colorname( obj->col1 ),
                 fli_query_colorname( obj->col2 ) );

    fl_free_object( defobj );
}
