set_pref_possibility(int which, long n, int save)
{
   char svalue[MAX_PREF_LEN];
   char *str=NULL;
   int r;

   if (which >= NUM_PREFS) {
      return EXIT_FAILURE;
   }
   if (glob_prefs[which].usertype == CHARTYPE) {
      get_pref_possibility(which, n, svalue);
      str=svalue;
   }
   r = jp_set_pref(glob_prefs, which, n, str);
   if (save) {
      pref_write_rc_file();
   }

   if (PREF_CHAR_SET == which)
      if (otherconv_init())
         printf("Error: could not set charset encoding\n");

   return r;
}
