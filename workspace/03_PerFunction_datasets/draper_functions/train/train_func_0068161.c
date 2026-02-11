builtin_export( FRAME * frame, int flags )
{
    LIST * const module_list = lol_get( frame->args, 0 );
    LIST * const rules = lol_get( frame->args, 1 );
    module_t * const m = bindmodule( list_empty( module_list ) ? 0 : list_front(
        module_list ) );

    LISTITER iter = list_begin( rules );
    LISTITER const end = list_end( rules );
    for ( ; iter != end; iter = list_next( iter ) )
    {
        RULE * r;
        if ( !m->rules || !( r = (RULE *)hash_find( m->rules, list_item( iter )
            ) ) )
            unknown_rule( frame, "EXPORT", m, list_item( iter ) );
        r->exported = 1;
    }
    return L0;
}
