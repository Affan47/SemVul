ralloc_vasprintf(const void *ctx, const char *fmt, va_list args)
{
   size_t size = printf_length(fmt, args) + 1;

   char *ptr = ralloc_size(ctx, size);
   if (ptr != NULL)
      vsnprintf(ptr, size, fmt, args);

   return ptr;
}
