fprint_name_value_list(
FILE *fp,
char *name,
lList *thresholds,
int print_slots,
int nm_name,
int nm_strval,
int nm_doubleval
) {
   lListElem *lep;
   int printed = 0;
   const char *s;
   char buffer[1024];

   DENTER(TOP_LAYER, "fprint_thresholds");

   FPRINTF((fp, "%s", name));

   for_each(lep, thresholds) {
      if (print_slots || strcmp("slots", lGetString(lep, nm_name))) {
         if (printed) {
            FPRINTF((fp, ","));
         }

         if (nm_strval == -1 || !(s=lGetString(lep, nm_strval))) {
            sprintf(buffer, "%f", lGetDouble(lep, nm_doubleval));
            s = buffer;
         }

         FPRINTF((fp, "%s=%s", lGetString(lep, nm_name), s));
         printed++;
      }
   }
   if (printed == 0) {
      FPRINTF((fp, "NONE\n"));
   } else {
      FPRINTF((fp, "\n"));
   }

   DEXIT;
   return 0;

FPRINTF_ERROR:
   DEXIT;
   return -1;
}
