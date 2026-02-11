set_bit(u32bit n)
   {
   const u32bit which = n / MP_WORD_BITS;
   const word mask = (word)1 << (n % MP_WORD_BITS);
   if(which >= size()) grow_to(which + 1);
   reg[which] |= mask;
   }
