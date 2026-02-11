nskip(s)
char *s;
   {
      char c;

      while (isdigit(c = *++s))
         ;
      if (c == 'r' || c == 'R') {
         while (isalnum(c = *++s))
            ;
         return s;
         }
      if (c == '.')
         while (isdigit (c = *++s))
            ;
      if (c == 'e' || c == 'E') {
         c = s[1];
         if (c == '+' || c == '-')
            s++;
         while (isdigit (c = *++s))
            ;
         }
      return s;
   }
