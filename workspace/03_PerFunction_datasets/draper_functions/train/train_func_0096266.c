BitVector_Word_Read(wordptr addr, N_int offset)
{
    N_word size = BV_SIZE_(addr);

    if (size > 0)
    {
        *(addr+size-1) &= BV_MASK_(addr);
        if (offset < size) return( *(addr+offset) );
    }
    return( (N_int) 0 );
}
