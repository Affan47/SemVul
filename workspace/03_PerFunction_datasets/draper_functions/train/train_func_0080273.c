strip_leading_space(char *str)
{
   char *p = str;

   while (B_ISSPACE(*p)) {
      p++;
   }
   if (p != str) {
      strcpy(str, p);
   }
}
