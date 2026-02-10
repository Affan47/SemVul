eina_str_tolower(char **str)
{
   char *p;
   if ((!str) || (!(*str)))
      return;

   for (p = *str; (*p); p++)
      *p = tolower((unsigned char )(*p));
}
