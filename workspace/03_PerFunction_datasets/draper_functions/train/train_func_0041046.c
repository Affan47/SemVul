mempref(const char * mem, const char * pref, size_t size)
{

   if (size < strlen(pref)) return 0;
   return ! memcmp(mem, pref, strlen(pref));
}
