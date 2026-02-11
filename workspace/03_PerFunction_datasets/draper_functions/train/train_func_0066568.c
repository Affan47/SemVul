BitVector_from_Hex(wordptr addr, charptr string)
{
    N_word  size = BV_SIZE_(addr);
    N_word  mask = BV_MASK_(addr);
    boolean ok = true;
    N_word  length;
    N_word  value;
    N_word  count;
    int     digit;

    if (size > 0)
    {
        length = strlen((char *) string);
        string += length;
        while (size-- > 0)
        {
            value = 0;
            for ( count = 0; (ok and (length > 0) and (count < BV_WordBits)); count += 4 )
            {
                digit = (int) *(--string); length--;

                digit = toupper(digit);
                if ((ok = (isxdigit(digit) != 0)))
                {
                    if (digit >= (int) 'A') digit -= (int) 'A' - 10;
                    else                    digit -= (int) '0';
                    value |= (((N_word) digit) << count);
                }
            }
            *addr++ = value;
        }
        *(--addr) &= mask;
    }
    if (ok) return(BV_ErrCode_Ok);
    else    return(BV_ErrCode_Pars);
}
