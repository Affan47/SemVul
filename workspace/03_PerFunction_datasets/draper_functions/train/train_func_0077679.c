endif(s)
char *s;
   {
   if (ifdepth <= curfile->ifdepth)
      return "unexpected $endif";
   if (*s != '\0')
      pfatal ("extraneous arguments on $else/$endif", s);
   ifdepth--;
   return NULL;
   }
