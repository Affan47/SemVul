string_set_insert( string_set * set, char const * string,
    int const size )
{
    unsigned hash = hash_keyval( string, size );
    unsigned pos = hash % set->num;

    struct hash_item * result;

    for ( result = set->data[ pos ]; result; result = result->header.next )
        if ( !strncmp( result->data, string, size ) && !result->data[ size ] )
            return result->data;

    if ( set->size >= set->num )
    {
        string_set_resize( set );
        pos = hash % set->num;
    }

    result = (struct hash_item *)allocate( sizeof( struct hash_header ) + size +
        1 );
    result->header.hash = hash;
    result->header.next = set->data[ pos ];
#ifndef NDEBUG
    result->header.magic = OBJECT_MAGIC;
#endif
    memcpy( result->data, string, size );
    result->data[ size ] = '\0';
    assert( hash_keyval( result->data, size ) == result->header.hash );
    set->data[ pos ] = result;
    strtotal += size + 1;
    ++set->size;

    return result->data;
}
