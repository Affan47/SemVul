SetBitCreate( void )
{
    bitWord  b1, b2;
    AT_NUMB n1, n2;
#ifdef INCHI_CANON_USE_HASH
    CtHash  h1, h2;
#endif
    int    i;

    if ( bBit ) {
        INCHI_HEAPCHK
        return 0;
    }

    b1 = 1;
    num_bit  = 1;
    for ( b1=1, num_bit=1; b1 < (b2 = (bitWord)((b1 << 1)& BIT_WORD_MASK)); b1 = b2, num_bit ++ )
        ;
    bBit = (bitWord*)inchi_calloc( num_bit, sizeof(bitWord));
    if ( !bBit ) {
        INCHI_HEAPCHK
        return -1;
    }
    for ( i = 0, b1=1; i < num_bit; i++, b1 <<= 1 ) {
        bBit[i] = b1;
    }

    for ( n1 = 1; n1 < (n2 = (AT_RANK)((n1 << 1)& AT_RANK_MASK) ); n1 = n2 )
        ;
    rank_mark_bit = n1;
    rank_mask_bit = ~n1;

#ifdef INCHI_CANON_USE_HASH
    for ( h1 = 1; h1 < (h2 = (h1 << 1)); h1 = h2 )
        ;
    hash_mark_bit = h1;
#endif
    INCHI_HEAPCHK
    return 1;
}
