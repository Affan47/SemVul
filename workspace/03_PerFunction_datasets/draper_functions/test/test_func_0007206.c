ugly_calloc(size_t count, size_t size, STRPTR file, ULONG line) {

   void *mem = ugly_malloc_tracking(count * size, file, line);


   if (mem) {
      memset(mem, 0, size * count);
   }
   return (mem);
}
