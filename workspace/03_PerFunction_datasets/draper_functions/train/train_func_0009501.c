estrjoin(const char *separator, ...)
{
   char *string, *s;
   va_list args;
   int len;
   int separator_len;

   if (separator == NULL)
      separator = "";

   separator_len = strlen(separator);
   va_start(args, separator);
   s = va_arg(args, char *);

   if (s)
   {
      len = strlen(s);
      s = va_arg(args, char *);

      while (s)
      {
         len += separator_len + strlen(s);
         s = va_arg(args, char *);
      }
      va_end(args);
      string = malloc(sizeof(char) * (len + 1));

      *string = 0;
      va_start(args, separator);
      s = va_arg(args, char *);

      strcat(string, s);
      s = va_arg(args, char *);

      while (s)
      {
         strcat(string, separator);
         strcat(string, s);
         s = va_arg(args, char *);
      }
   }
   else
      string = estrdup("");
   va_end(args);

   return string;
}
