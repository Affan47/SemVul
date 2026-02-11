open_dict_file(const char *dict_file_name) {
   char *fn;
   FILE *fp;
#ifdef __CYGWIN__
   char fnbuf[MAXLINE];
   int fnbuf_siz;
   int i;
#endif

   if (dict_file_name[0] == '\0') {
#ifdef __CYGWIN__
      if ((fnbuf_siz=GetModuleFileName(GetModuleHandle(0),
           fnbuf, MAXLINE)) == 0) {
         err_msg("ERROR: Call to GetModuleFileName failed");
      }
      for (i=fnbuf_siz-1; i>=0 && fnbuf[i] != '/' && fnbuf[i] != '\\'; i--)
         ;
      if (i >= 0) {
         fnbuf[i] = '\0';
      }
      fn = make_message("%s\\%s", fnbuf, DICT_FILE);
#else
      fn = make_message("%s/%s", IKEDATADIR, DICT_FILE);
#endif
   } else {
      fn = make_message("%s", dict_file_name);
   }

   if ((strcmp(fn, "-")) == 0) {
      fp = stdin;
   } else {
      if ((fp = fopen(fn, "r")) == NULL) {
         err_sys("error opening dictionary file %s", fn);
      }
   }
   free(fn);

   return fp;
}
