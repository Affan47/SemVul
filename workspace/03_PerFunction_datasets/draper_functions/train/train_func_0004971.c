bigint_sub2(word x[], u32bit x_size, const word y[], u32bit y_size)
   {
   word carry = 0;

   const u32bit blocks = y_size - (y_size % 8);

   for(u32bit j = 0; j != blocks; j += 8)
      carry = word8_sub2(x + j, y + j, carry);

   for(u32bit j = blocks; j != y_size; ++j)
      x[j] = word_sub(x[j], y[j], &carry);

   if(!carry) return;

   for(u32bit j = y_size; j != x_size; ++j)
      {
      --x[j];
      if(x[j] != MP_WORD_MAX) return;
      }
   }
