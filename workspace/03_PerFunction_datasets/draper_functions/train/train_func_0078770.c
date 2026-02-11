newchunk(n)
u_int n;
{
   struct chunk *cp;
   int k, size;


   n = (n + sizeof(long) - 1) & ~(sizeof(long) - 1);

   cp = &chunks[cur_chunk];
   if (n > cp->n_left) {
      ++cp, k = ++cur_chunk;
      if (k >= NCHUNKS)
         ArgusLog(LOG_ERR,"out of memory");
      size = CHUNK0SIZE << k;
      cp->m = (void *)malloc(size);
      memset((char *)cp->m, 0, size);
      cp->n_left = size;
      if (n > size)
         ArgusLog(LOG_ERR,"out of memory");
   }
   cp->n_left -= n;
   return (void *)((char *)cp->m + cp->n_left);
}
