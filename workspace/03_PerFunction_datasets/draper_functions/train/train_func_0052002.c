mallocSprintf (char **Ptr, const char *fmt, ...)
{
   va_list ap;
   size_t buff_len = 0;

   *Ptr = NULL;
   if (fmt != NULL) {
      va_start (ap, fmt);
      AllocSprintf (Ptr, &buff_len, fmt, ap);
      va_end (ap);
   }
}
