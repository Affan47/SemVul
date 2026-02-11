bigint_shl2(word y[], const word x[], u32bit x_size,
                 u32bit word_shift, u32bit bit_shift)
   {
   for(u32bit j = 0; j != x_size; ++j)
      y[j + word_shift] = x[j];
   if(bit_shift)
      {
      word carry = 0;
      for(u32bit j = word_shift; j != x_size + word_shift + 1; ++j)
         {
         word temp = y[j];
         y[j] = (temp << bit_shift) | carry;
         carry = (temp >> (MP_WORD_BITS - bit_shift));
         }
      }
   }
