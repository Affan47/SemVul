rline(fp)
FILE *fp;
   {
#define LINE_SIZE_INIT 100
#define LINE_SIZE_INCR 100
   static char *lbuf = NULL;
   static int llen = 0;
   register char *p;
   register int c, n;


   if (!lbuf) {
      lbuf = alloc(LINE_SIZE_INIT);
      llen = LINE_SIZE_INIT;
      }


   c = getc(fp);
   if (c == EOF)
      return NULL;
   if (c == '\n')
      return "\n";

   p = lbuf;
   n = llen - 3;
   *p++ = c;

   for (;;)  {

      while (--n >= 0 && (c = getc(fp)) != '\n' && c != EOF)
         *p++ = c;
      if (n >= 0) {
         *p++ = '\n';
         *p++ = '\0';
         return lbuf;
         }


      llen += LINE_SIZE_INCR;
      lbuf = realloc(lbuf, (unsigned int)llen);
      if (!lbuf) {
         fprintf(stderr, "rline(%d): out of memory\n", llen);
         exit(EXIT_FAILURE);
         }
      p = lbuf + llen - LINE_SIZE_INCR - 2;
      n = LINE_SIZE_INCR;
      }
   }
