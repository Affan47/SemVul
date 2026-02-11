Clock_PrintZone2 (char *ptr, sChar TimeZone, char f_day)
{
   if (TimeZone == 0) {
      sprintf (ptr, "UTC");
      return 0;
   } else if (TimeZone == 5) {
      if (f_day) {
         sprintf (ptr, "EDT");
      } else {
         sprintf (ptr, "EST");
      }
      return 0;
   } else if (TimeZone == 6) {
      if (f_day) {
         sprintf (ptr, "CDT");
      } else {
         sprintf (ptr, "CST");
      }
      return 0;
   } else if (TimeZone == 7) {
      if (f_day) {
         sprintf (ptr, "MDT");
      } else {
         sprintf (ptr, "MST");
      }
      return 0;
   } else if (TimeZone == 8) {
      if (f_day) {
         sprintf (ptr, "PDT");
      } else {
         sprintf (ptr, "PST");
      }
      return 0;
   } else if (TimeZone == 9) {
      if (f_day) {
         sprintf (ptr, "YDT");
      } else {
         sprintf (ptr, "YST");
      }
      return 0;
   }
   ptr[0] = '\0';
   return -1;
}
