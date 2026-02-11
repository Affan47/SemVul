BitVector_Chunk_Store(wordptr addr, N_int chunksize, N_int offset,
                           N_long value)
{
    N_word bits = BV_BITS_(addr);
    N_word mask;
    N_word temp;

    if ((chunksize > 0) and (offset < bits))
    {
        if (chunksize > BV_LongBits) chunksize = BV_LongBits;
        if ((offset + chunksize) > bits) chunksize = bits - offset;
        addr += offset >> BV_LogBits;
        offset &= BV_ModMask;
        while (chunksize > 0)
        {
            mask = (N_word) (~0L << offset);
            bits = offset + chunksize;
            if (bits < BV_WordBits)
            {
                mask &= (N_word) ~(~0L << bits);
                bits = chunksize;
            }
            else bits = BV_WordBits - offset;
            temp = (N_word) (value << offset);
            temp &= mask;
            *addr &= NOT mask;
            *addr++ |= temp;
            value >>= bits;
            chunksize -= bits;
            offset = 0;
        }
    }
}
