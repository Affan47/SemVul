BitVector_Block_Store(wordptr addr, charptr buffer, N_int length)
{
    N_word  size = BV_SIZE_(addr);
    N_word  mask = BV_MASK_(addr);
    N_word  value;
    N_word  count;


    if (size > 0)
    {
        while (size-- > 0)
        {
            value = 0;
            for ( count = 0; (length > 0) and (count < BV_WordBits); count += 8 )
            {
                value |= (((N_word) *buffer++) << count); length--;
            }
            *addr++ = value;
        }
        *(--addr) &= mask;
    }
}
