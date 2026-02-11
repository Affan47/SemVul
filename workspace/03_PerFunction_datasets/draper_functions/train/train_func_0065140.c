str_search(const char *needle, const char *haystack, int haystack_len)
{
   int needle_len = strlen(needle);

   while (haystack_len-- >= needle_len)
   {
      if (memcmp(needle, haystack, needle_len) == 0)
      {
         return(haystack);
      }
      haystack++;
   }
   return(NULL);
}
