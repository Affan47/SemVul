_mime_shell_script_check(const char *mime)
{
   static const struct sh_script_map {
      const char *str;
      size_t len;
   } options[] = {
#define O(x) {x, sizeof(x) - 1}
     O("application/x-sh"),
     O("application/x-shellscript"),
     O("text/x-sh"),
#undef O
     {NULL, 0}
   };
   const struct sh_script_map *itr;
   size_t mimelen = strlen(mime);

   for (itr = options; itr->str != NULL; itr++)
     if ((mimelen == itr->len) && (memcmp(mime, itr->str, mimelen) == 0))
       return EINA_TRUE;

   return EINA_FALSE;
}
