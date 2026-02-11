SetRangeOn(unsigned lo_bit_offset, unsigned hi_bit_offset)
  {
    if (lo_bit_offset > hi_bit_offset)
      return;
    else if (lo_bit_offset == hi_bit_offset)
      SetBitOn(hi_bit_offset);
    else
      {
        unsigned lo_word_offset = lo_bit_offset >> WORDROLL;
        unsigned hi_word_offset = hi_bit_offset >> WORDROLL;
        lo_bit_offset &= WORDMASK;
        hi_bit_offset &= WORDMASK;

        if (hi_word_offset >= GetSize())
          ResizeWords(hi_word_offset + 1);

        if (lo_word_offset == hi_word_offset)
          {
            for ( unsigned i = lo_bit_offset ; i <= hi_bit_offset ; i++ )
              _set[lo_word_offset] |= (1<<i);
          }
        else
          {
            for ( unsigned i = lo_bit_offset ; i < SETWORD ; ++ i )
              _set[lo_word_offset] |= (1<<i);
            for ( unsigned i = lo_word_offset + 1 ; i < hi_word_offset ; ++ i )
              _set[i] = 0xFFFFFFFF;
            for ( unsigned i = 0 ; i <= hi_bit_offset ; ++ i )
              _set[hi_word_offset] |= (1<<i);
          }
      }
  }
