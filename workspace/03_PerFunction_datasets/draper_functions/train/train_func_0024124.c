bregexp_build_where(char *dest, int str_size,
                          char *strip_prefix,
                          char *add_prefix,
                          char *add_suffix)
{
   int len=0;

   POOLMEM *str_tmp = get_memory(str_size);

   *str_tmp = *dest = '\0';

   if (strip_prefix) {
      len += bsnprintf(dest, str_size - len, str_strip_prefix,
                       bregexp_escape_string(str_tmp, strip_prefix, regexp_sep));
   }

   if (add_suffix) {
      if (len) dest[len++] = ',';

      len += bsnprintf(dest + len,  str_size - len, str_add_suffix,
                       bregexp_escape_string(str_tmp, add_suffix, regexp_sep));
   }

   if (add_prefix) {
      if (len) dest[len++] = ',';

      len += bsnprintf(dest + len, str_size - len, str_add_prefix,
                       bregexp_escape_string(str_tmp, add_prefix, regexp_sep));
   }

   free_pool_memory(str_tmp);

   return dest;
}
