BitVector_Delete(wordptr addr, N_int offset, N_int count, boolean clear)
{
    N_word bits = BV_BITS_(addr);
    N_word last;

    if ((count > 0) and (offset < bits))
    {
        last = offset + count;
        if (last < bits)
        {
            BitVector_Interval_Copy(addr,addr,offset,last,(bits-last));
        }
        else count = bits - offset;
        if (clear) BitVector_Interval_Empty(addr,(bits-count),(bits-1));
    }
}
