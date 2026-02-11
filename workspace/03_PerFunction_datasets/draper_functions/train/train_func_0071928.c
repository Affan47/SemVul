bigint_shr1(word x[], u32bit x_size, u32bit word_shift, u32bit bit_shift)
   {
   if(x_size < word_shift)
      {
      clear_mem(x, x_size);
      return;
      }

   if(word_shift)
      {
      for(u32bit j = 0; j != x_size - word_shift; ++j)
         x[j] = x[j + word_shift];
      for(u32bit j = x_size - word_shift; j != x_size; ++j)
         x[j] = 0;
      }

   if(bit_shift)
      {
      word carry = 0;
      for(u32bit j = x_size - word_shift; j > 0; --j)
         {
         word temp = x[j-1];
         x[j-1] = (temp >> bit_shift) | carry;
         carry = (temp << (MP_WORD_BITS - bit_shift));
         }
      }
   }
