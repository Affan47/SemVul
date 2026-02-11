copy_argv(argv)
char **argv;
{
   char **p;
   int len = 0;
   char *argus_strbuf;
   char *src, *dst;

   p = argv;
   if (*p == 0)
      return 0;

   while (*p)
      len += strlen(*p++) + 1;

   argus_strbuf = (char *) malloc (len);

   p = argv;
   dst = argus_strbuf;
   while ((src = *p++) != NULL) {
      while ((*dst++ = *src++) != '\0')
         ;
      dst[-1] = ' ';
   }
   dst[-1] = '\0';

   return argus_strbuf;
}
