int_get(const char *buf)
{
   const char *p = strchr(buf, ':');
   if (!p) return 0;
   p++;
   while (*p == ' ')
     p++;
   return atoi(p);
}
