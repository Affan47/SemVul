removenonprintable(char *str1) {
   int i;
   unsigned char *str = (unsigned char*)str1;

   if (!str) return NULL;

   for (i=0; i<strlen(str); i++) {
      if (!((str[i] >= 0x20 && str[i] <= 0x7E) ||
            (str[i] >= 0xA1) ||
            str[i] == 0x01 ||
            str[i] == 0x02 ||
            str[i] == 0x03 ||
            str[i] == 0x09 ||
            str[i] == 0x0A ||
            str[i] == 0x0D ||
            str[i] == 0x0F ||
            str[i] == 0x16 ||
            str[i] == 0x1F ))
      str[i] = '.';

      }
   return str;
   }
