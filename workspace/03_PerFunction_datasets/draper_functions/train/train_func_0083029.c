list_append( LIST * l, LIST * nl )
{
    if ( list_empty( l ) )
        return nl;
    if ( !list_empty( nl ) )
    {
        int const l_size = list_length( l );
        int const nl_size = list_length( nl );
        int const size = l_size + nl_size;
        unsigned const bucket = get_bucket( size );


        if ( l_size <= ( 1u << ( bucket - 1 ) ) )
        {
            LIST * result = list_alloc( size );
            memcpy( list_begin( result ), list_begin( l ), l_size * sizeof(
                OBJECT * ) );
            list_dealloc( l );
            l = result;
        }

        l->impl.size = size;
        memcpy( list_begin( l ) + l_size, list_begin( nl ), nl_size * sizeof(
            OBJECT * ) );
        list_dealloc( nl );
    }
    return l;
}
