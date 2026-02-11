findFreeRange(unsigned int count) const
{
   const uint32_t m = (1 << count) - 1;
   int pos = size;
   unsigned int i;
   const unsigned int end = (size + 31) / 32;

   if (count == 1) {
      for (i = 0; i < end; ++i) {
         pos = ffs(~data[i]) - 1;
         if (pos >= 0)
            break;
      }
   } else
   if (count == 2) {
      for (i = 0; i < end; ++i) {
         if (data[i] != 0xffffffff) {
            uint32_t b = data[i] | (data[i] >> 1) | 0xaaaaaaaa;
            pos = ffs(~b) - 1;
            if (pos >= 0)
               break;
         }
      }
   } else
   if (count == 4 || count == 3) {
      for (i = 0; i < end; ++i) {
         if (data[i] != 0xffffffff) {
            uint32_t b =
               (data[i] >> 0) | (data[i] >> 1) |
               (data[i] >> 2) | (data[i] >> 3) | 0xeeeeeeee;
            pos = ffs(~b) - 1;
            if (pos >= 0)
               break;
         }
      }
   } else {
      if (count <= 8)
         count = 8;
      else
      if (count <= 16)
         count = 16;
      else
         count = 32;

      for (i = 0; i < end; ++i) {
         if (data[i] != 0xffffffff) {
            for (pos = 0; pos < 32; pos += count)
               if (!(data[i] & (m << pos)))
                  break;
            if (pos < 32)
               break;
         }
      }
   }
   pos += i * 32;

   return ((pos + count) <= size) ? pos : -1;
}
