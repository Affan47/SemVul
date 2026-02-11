contains(void* ptr,
                                               u32bit length) const throw()
   {
   return ((buffer <= ptr) &&
           (buffer_end >= (byte*)ptr + length * BLOCK_SIZE));
   }
