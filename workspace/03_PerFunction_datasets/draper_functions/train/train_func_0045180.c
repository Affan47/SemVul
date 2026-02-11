headers( TARGET * t )
{
    LIST   * hdrscan;
    LIST   * hdrrule;
    #ifndef OPT_HEADER_CACHE_EXT
    LIST   * headlist = L0;
    #endif
    regexp * re[ MAXINC ];
    int rec = 0;
    LISTITER iter;
    LISTITER end;

    hdrscan = var_get( root_module(), constant_HDRSCAN );
    if ( list_empty( hdrscan ) )
        return;

    hdrrule = var_get( root_module(), constant_HDRRULE );
    if ( list_empty( hdrrule ) )
        return;

    if ( DEBUG_HEADER )
        printf( "header scan %s\n", object_str( t->name ) );


    iter = list_begin( hdrscan );
    end = list_end( hdrscan );
    for ( ; ( rec < MAXINC ) && iter != end; iter = list_next( iter ) )
    {
        re[ rec++ ] = regex_compile( list_item( iter ) );
    }


    {
        FRAME frame[ 1 ];
        frame_init( frame );
        lol_add( frame->args, list_new( object_copy( t->name ) ) );
#ifdef OPT_HEADER_CACHE_EXT
        lol_add( frame->args, hcache( t, rec, re, hdrscan ) );
#else
        lol_add( frame->args, headers1( headlist, t->boundname, rec, re ) );
#endif

        if ( lol_get( frame->args, 1 ) )
        {
            OBJECT * rulename = list_front( hdrrule );

            lol_add( frame->args, list_new( object_copy( t->boundname ) ) );
            list_free( evaluate_rule( bindrule( rulename, frame->module ), rulename, frame ) );
        }


        frame_free( frame );
    }
}
