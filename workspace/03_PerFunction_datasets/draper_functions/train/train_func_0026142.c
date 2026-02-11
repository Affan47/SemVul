strdel(char *str, size_t len)
{
   size_t              length = strlen(str);

   if (len > length)
      len = length;
   memmove(str, str + len, length - len + 1);
   return str;
}
