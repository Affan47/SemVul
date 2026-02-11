_erealloc(void *ptr, size_t n)
{
   void *p;

   p = realloc(ptr, n);
   if (p == NULL)
      eprintf("realloc of %p by %u bytes failed:", ptr, n);
   return p;
}
