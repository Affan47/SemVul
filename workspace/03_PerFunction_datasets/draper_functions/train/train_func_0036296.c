oldhelp(char *name[], char *val[], int cnt, char *product, char *content,
		char *token)
{
   char  path[PATH_LENGTH];
   FILE *frameset  = NULL;

   if (debugPrintout)
   {
	   printf( "Old help\n\n" );
   }


   safe_snprintf(path, sizeof(path), "%s%c%s%c%s%c%s", MANUALDIR, FILE_SEP, locale, FILE_SEP, product, FILE_SEP, FRAMESET_FILE);
   if (debugPrintout)
   {
	   printf("opening frameset file: %s<P>\n", path);
   }
   if (!(frameset = fopen(path, "r")))
   {

      safe_snprintf(path, sizeof(path), "%s%c%s%c%s%c%s", MANUALDIR, FILE_SEP, HELPSUBDIR, FILE_SEP, FRAMESET_FILE);
      if (!(frameset = fopen(path, "r")))
	  {
		  if (debugPrintout)
		  {
			  printf("unable to open a valid frameset file: %s<P>\n", path);
			  fflush( stdout );
		  }
		  return error_exit("unable to open a valid frameset file");
	  }
   }

   if (debugPrintout)
   {
	   printf("reading frameset file: %s<P>\n", path);
   }


   if (!didContentHeader)
   {
	   printf("Content-type: text/html\n\n");
   }

   while (fgets(path, PATH_LENGTH, frameset))
   {
      char *f, *p;

      if ((f = caseless_strstr(path, HEAD_BLOCK)))
      {


         p = path;
         while (p < f + strlen(HEAD_BLOCK))
	    putchar(*(p++));

         printf("<script type=\"text/javascript\">\n");
         printf("%s=\"%s\";\n", DIR_VAR, product);
	 printf("%s=window;\n", HELPWIN_VAR);
         printf("</script>\n");

         while (*p)
	    putchar(*(p++));

         continue;
      }

      if (!(f = caseless_strstr(path, FRAME_BLOCK)) || !caseless_strstr(path, CONTENT_FRAME))
      {
	 fputs(path, stdout);
	 continue;
      }


      p = path;
      while (p < f + strlen(FRAME_BLOCK))
	 putchar(*(p++));

      printf("src=\"%s%c%s%c%s%c%s\" ", BASE_DIR, FILE_SEP, locale, FILE_SEP, product, FILE_SEP, content);

      while (*p)
	 putchar(*(p++));
   }


   fflush(stdout);
   fclose(frameset);
   return 0;
}
