fl_set_xyplot_data( FL_OBJECT  * ob,
                    float      * x,
                    float      * y,
                    int          n,
                    const char * title,
                    const char * xlabel,
                    const char * ylabel )
{
    FLI_XYPLOT_SPEC *sp = ob->spec;

#if FL_DEBUG >= ML_ERR
    if ( ! IsValidClass( ob, FL_XYPLOT ) )
    {
        M_err( "fl_set_xyplot_data", "%s not an xyplot", ob ? ob->label : "" );
        return;
    }
#endif

    free_overlay_data( sp, 0 );

    fl_safe_free( sp->xlabel );
    fl_safe_free( sp->ylabel );
    fl_safe_free( sp->title );

    sp->xlabel = fl_strdup( xlabel ? xlabel : "" );
    sp->ylabel = fl_strdup( ylabel ? ylabel : "" );
    sp->title = fl_strdup( title ? title : "" );

    *sp->x = fl_malloc( n * sizeof **sp->x );
    *sp->y = fl_malloc( n * sizeof **sp->y );

    if ( ! *sp->x || ! *sp->y )
    {
        if ( *sp->x )
            fl_free( *sp->x );
        M_err( "fl_set_xyplot_data", "Can't allocate memory" );
        return;
    }

    extend_screen_data( sp, n );

    memcpy( *sp->x, x, n * sizeof **sp->x );
    memcpy( *sp->y, y, n * sizeof **sp->y );
    *sp->n = n;

    find_xbounds( sp );
    find_ybounds( sp );

    fl_redraw_object( ob );
}
