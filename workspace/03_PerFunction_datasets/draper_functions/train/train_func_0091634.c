list_in( LIST * l, OBJECT * value )
{
    LISTITER iter = list_begin( l );
    LISTITER end = list_end( l );
    for ( ; iter != end; iter = list_next( iter ) )
        if ( object_equal( list_item( iter ), value ) )
            return 1;
    return 0;
}
