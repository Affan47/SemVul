dotcat(char *dest, const char *src)
{
   int len = strlen(dest);
   const char *s;
   char *d;

   for (d = dest + len, s = src; *s; d++, s++) *d = tolower(*s);
   *d = 0;
}
