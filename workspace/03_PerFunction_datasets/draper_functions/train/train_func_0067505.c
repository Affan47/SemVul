allocate( size_t n )
{
#ifdef BJAM_NEWSTR_NO_ALLOCATE
    return (char *)BJAM_MALLOC( n );
#else

    size_t remaining = storage_finish - storage_start;
    n = ( ( n + ALLOC_ALIGNMENT - 1 ) / ALLOC_ALIGNMENT ) * ALLOC_ALIGNMENT;
    if ( remaining >= n )
    {
        char * result = storage_start;
        storage_start += n;
        return result;
    }
    else
    {
        strblock * new_block;
        size_t nalloc = n;
        if ( nalloc < STRING_BLOCK )
            nalloc = STRING_BLOCK;


        new_block = (strblock *)BJAM_MALLOC( offsetof( strblock, data[ 0 ] ) +
            nalloc * sizeof( new_block->data[ 0 ] ) );
        if ( new_block == 0 )
            return 0;
        new_block->next = strblock_chain;
        strblock_chain = new_block;


        if ( remaining < nalloc - n )
        {
            storage_start = new_block->data + n;
            storage_finish = new_block->data + nalloc;
        }
        return new_block->data;
    }
#endif
}
