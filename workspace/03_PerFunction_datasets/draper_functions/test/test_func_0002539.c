instr(char *s, const char *find, char separ)
{
char *t, c, sc;
int len;

   if (!s || !find)
      return NULL;
   if (separ) {
      t = s;
      if ((s = strrchr(s, separ)) == NULL)
         s = t;
      else
         s++;
   }
   if ((c = *find++) != 0) {
      len = strlen(find);
      do {
         do {
            if ((sc = *s++) == 0)
               return NULL;
         } while (sc != c);
      } while (strncmp(s, find, len) != 0);
      s--;
   }
   return s;
}
