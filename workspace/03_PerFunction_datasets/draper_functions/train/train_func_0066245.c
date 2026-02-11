list_cmp( LIST * t, LIST * s )
{
    int status = 0;
    LISTITER t_it = list_begin( t );
    LISTITER const t_end = list_end( t );
    LISTITER s_it = list_begin( s );
    LISTITER const s_end = list_end( s );

    while ( !status && ( t_it != t_end || s_it != s_end ) )
    {
        char const * st = t_it != t_end ? object_str( list_item( t_it ) ) : "";
        char const * ss = s_it != s_end ? object_str( list_item( s_it ) ) : "";

        status = strcmp( st, ss );

        t_it = t_it != t_end ? list_next( t_it ) : t_it;
        s_it = s_it != s_end ? list_next( s_it ) : s_it;
    }

    return status;
}
