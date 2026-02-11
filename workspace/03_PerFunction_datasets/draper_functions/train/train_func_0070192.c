ugly_realloc(void *ptr, size_t size, STRPTR file, ULONG line) {
   void *newptr = ugly_malloc_tracking(size, file, line);
   UGLYMEM *umem = find_umem(ptr);

   if (newptr && umem) {

      memcpy(newptr, umem->ptr, umem->size);

      ugly_free(ptr, file, line);
   }
   return (newptr);
}
