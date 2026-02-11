setArgusWfile(char *file, char *filter)
{
   FILE *fd = NULL;
   struct ArgusWfileStruct *wfile = NULL;
   char realpathname[PATH_MAX], *ptr = NULL;
   int euid = geteuid();

   if (ArgusWfileList == NULL)
      ArgusWfileList = ArgusNewList();

   if (file) {
      if (strcmp (file, "-")) {
         setuid(getuid());
         if ((fd = fopen (file, "a+")) != NULL) {
            bzero (realpathname, PATH_MAX);
            if ((ptr = realpath (file, realpathname)) == NULL)
               ArgusLog (LOG_ERR, "setArgusWfile, realpath %s %s\n", file, strerror(errno));
            else
               ptr = strdup(ptr);

            fclose (fd);

         } else {
#ifdef ARGUSDEBUG
            ArgusDebug (1, "setArgusWfile, open %s %s\n", file, strerror(errno));
#endif
         }
         setuid(euid);
      } else
         ptr = strdup(file);

      if ((wfile = (struct ArgusWfileStruct *) ArgusCalloc (1, sizeof (*wfile))) != NULL) {
         wfile->filename = ptr;
         if (filter)
            wfile->filter = strdup(filter);
         ArgusPushFrontList(ArgusWfileList, wfile);

      } else
         ArgusLog (LOG_ERR, "setArgusWfile, ArgusCalloc %s\n", strerror(errno));
   } else
      ArgusLog (LOG_ERR, "setArgusWfile, file is null\n");
}
