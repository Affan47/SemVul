list_free( LIST * head )
{
    if ( !list_empty( head ) )
    {
        LISTITER iter = list_begin( head ), end = list_end( head );
        for ( ; iter != end; iter = list_next( iter ) )
        {
            object_free( list_item( iter ) );
        }
        list_dealloc( head );
    }
}
