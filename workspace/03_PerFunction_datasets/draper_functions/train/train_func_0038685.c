list_copy_range( LIST * l, LISTITER first, LISTITER last )
{
    if ( first == last )
        return L0;
    else
    {
        int size = last - first;
        LIST * result = list_alloc( size );
        LISTITER dest = list_begin( result );
        result->impl.size = size;
        for ( ; first != last; ++first, ++dest )
            *dest = object_copy( *first );
        return result;
    }
}
