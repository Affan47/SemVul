save_object( FILE      * fl,
             FL_OBJECT * obj )
{
    char name[ MAX_VAR_LEN ],
         cbname[ MAX_VAR_LEN ],
         argname[ MAX_VAR_LEN ];
    char *label;
    double sc = get_conversion_factor( );
    FL_OBJECT *defobj,
              fake_obj;

    if ( obj->parent )
        return;

    defobj = find_class_default( obj->objclass, obj->type );

    get_object_name( obj, name, cbname, argname );

    fprintf( fl, "\n--------------------\n" );
    fprintf( fl, "class: %s\n", class_name( obj->objclass ) );
    fprintf( fl, "type: %s\n", find_type_name( obj->objclass, obj->type ) );

    fake_obj.x = obj->x;
    fake_obj.y = obj->y;
    fake_obj.w = obj->w;
    fake_obj.h = obj->h;
    fl_scale_object( &fake_obj, sc, sc );
    fprintf( fl, "box: %d %d %d %d\n", fake_obj.x, fake_obj.y,
             fake_obj.w, fake_obj.h );

    fprintf( fl, "boxtype: %s\n", boxtype_name( obj->boxtype ) );
    fprintf( fl, "colors: %s %s\n", fli_query_colorname( obj->col1 ),
             fli_query_colorname( obj->col2 ) );
    fprintf( fl, "alignment: %s\n", align_name( obj->align, 0 ) );
    fprintf( fl, "style: %s\n", style_name( obj->lstyle ) );
    fprintf( fl, "size: %s\n", lsize_name( obj->lsize ) );
    fprintf( fl, "lcol: %s\n", fli_query_colorname( obj->lcol ) );
    label = get_label( obj, 0 );
    fprintf( fl, "label: %s\n", label );
    fl_free( label );
    fprintf( fl, "shortcut: %s\n", get_shortcut_string( obj ) );
    fprintf( fl, "resize: %s\n", resize_name( obj->resize ) );
    fprintf( fl, "gravity: %s %s\n",
             gravity_name( obj->nwgravity ),
             gravity_name( obj->segravity ) );
    fprintf( fl, "name: %s\n", name );
    fprintf( fl, "callback: %s\n", cbname );
    fprintf( fl, "argument: %s\n", argname );
    if ( ! defobj || obj->how_return != defobj->how_return )
        fprintf( fl, "return: %s\n",
                 get_how_return_name( obj->how_return, 0 ) );

    save_objclass_spec_info( fl, obj );
}
