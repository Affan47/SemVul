hash_malloc(int size)
{
   int mb_size;
   char *buf;
   int asize = BALIGN(size);

   if (mem_block->rem < asize) {
      if (total_size >= (extend_length / 2)) {
         mb_size = extend_length;
      } else {
         mb_size = extend_length / 2;
      }
      malloc_big_buf(mb_size);
      Dmsg1(100, "Created new big buffer of %ld bytes\n", mb_size);
   }
   mem_block->rem -= asize;
   buf = mem_block->mem;
   mem_block->mem += asize;
   return buf;
}
