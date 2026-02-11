ArgusEncodeAscii (const char *ptr, int len, char *str, int slen)
{
   int retn = 0, newlen = len;
   unsigned char *buf = (unsigned char *) str;

   if (ptr && (len < slen)) {
      while (len > 0) {
         if (isascii((int)*ptr) && isprint((int)*ptr))
            *buf = *ptr;
         else
            *buf = '.';
         buf++;
         ptr++;
         len--;
      }

      if (!(Pflag)) {
         if ((buf = (unsigned char *) strstr (str, "PASS")) != NULL) {
            buf += 5;
            while (((void *)(str + newlen) > (void *) buf) && ((*buf != ' ') && (*buf != '.')))
               *buf++ = 'x';
         }
      }

      retn = newlen;
   }

   return (retn);
}
