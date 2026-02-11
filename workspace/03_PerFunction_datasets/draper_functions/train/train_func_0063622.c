set_pref(int which, long n, const char *string, int save)
{
   const char *str;
   int r;

   if (which >= NUM_PREFS) {
      return EXIT_FAILURE;
   }
   str=string;
   if ((which==PREF_RCFILE) ||
       (which==PREF_SHORTDATE) ||
       (which==PREF_LONGDATE) ||
       (which==PREF_TIME) ||
       (which==PREF_PAPER_SIZE)) {
      set_pref_possibility(which, n, FALSE);
      str=glob_prefs[which].svalue;
   }
   r = jp_set_pref(glob_prefs, which, n, str);
   if (save) {
      pref_write_rc_file();
   }

   return r;
}
