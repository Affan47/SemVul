getLocale() {
   char *loc;
   char path[PATH_LENGTH];
   SYS_DIR *dir = NULL;


   loc = strtok(strdup(localeList), ",");
   while (1){
      if (loc) {
	safe_snprintf(path, sizeof(path), "%s%c%c%c", MANUALDIR, FILE_SEP, loc[0], loc[1]);
	if ((dir = dir_open(path))) {

	  loc[2] = '\0';
	  dir_close(dir);
	  return loc;
	}
      }
      loc = strtok(NULL, ",");
      if (!loc) {

         safe_snprintf(path, sizeof(path), "%s%c%s", MANUALDIR, FILE_SEP, DEFAULT_LANG);
         if ((dir = dir_open(path))) {
	    dir_close(dir);
            return DEFAULT_LANG;
	 } else {
            error_exit("No help available for any of the languages set for the browser");
	 }
      }
   }
}
