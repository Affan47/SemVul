sge_dstring_vsprintf_copy_append(dstring *sb,
                                 sge_dstring_copy_append_f function,
                                 const char *format,
                                 va_list ap)
{
   const char *ret = NULL;

   if (sb != NULL && format != NULL && function != NULL) {
      char static_buffer[BUFSIZ];
      int vsnprintf_ret;
      va_list ap_copy;

      va_copy(ap_copy, ap);
      vsnprintf_ret = vsnprintf(static_buffer, BUFSIZ, format, ap_copy);
      va_end(ap_copy);


      if (vsnprintf_ret == -1) {
         size_t dyn_size = 2 * BUFSIZ;
         char *dyn_buffer = sge_malloc(dyn_size);

         while (vsnprintf_ret == -1 && dyn_buffer != NULL) {
            va_copy(ap_copy, ap);
            vsnprintf_ret = vsnprintf(dyn_buffer, dyn_size, format, ap_copy);
            va_end(ap_copy);

            if (vsnprintf_ret == -1) {
               dyn_size *= 2;
               dyn_buffer = sge_realloc(dyn_buffer, dyn_size, 0);
            }
         }
         if (dyn_buffer != NULL) {
            ret = function(sb, dyn_buffer);
            sge_free(dyn_buffer);
         } else {

            ret = NULL;
         }
      } else if (vsnprintf_ret > BUFSIZ) {
         char *dyn_buffer = NULL;

         dyn_buffer = (char *)malloc((vsnprintf_ret + 1) * sizeof(char));
         if (dyn_buffer != NULL) {
            va_copy(ap_copy, ap);
            vsnprintf(dyn_buffer, vsnprintf_ret + 1, format, ap_copy);
            va_end(ap_copy);

            ret = function(sb, dyn_buffer);
            sge_free(dyn_buffer);
         } else {

            ret = NULL;
         }
      } else {
         ret = function(sb, static_buffer);
      }
   }
   return ret;
}
