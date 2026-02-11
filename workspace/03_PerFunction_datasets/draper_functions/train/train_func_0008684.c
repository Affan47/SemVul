list_dealloc( LIST * l )
{
    unsigned size = list_length( l );
    unsigned bucket;
    struct freelist_node * node = (struct freelist_node *)l;

    if ( size == 0 ) return;

    bucket = get_bucket( size );;

#ifdef BJAM_NO_MEM_CACHE

    BJAM_FREE( node );

#else

    node->next = freelist[ bucket ];
    freelist[ bucket ] = node;

#endif

}
