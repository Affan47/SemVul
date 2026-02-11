is_master(const char* progname) {
   if (progname != NULL) {
      if ( !strcmp(prognames[QMASTER],progname)) {
         return true;
      }
   }
   return false;
}
