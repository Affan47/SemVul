store_runscript_target(LEX *lc, RES_ITEM *item, int index, int pass)
{
   lex_get_token(lc, T_STRING);

   if (pass == 2) {
      if (strcmp(lc->str, "%c") == 0) {
         ((RUNSCRIPT*) item->value)->set_target(lc->str);
      } else if (strcasecmp(lc->str, "yes") == 0) {
         ((RUNSCRIPT*) item->value)->set_target("%c");
      } else if (strcasecmp(lc->str, "no") == 0) {
         ((RUNSCRIPT*) item->value)->set_target("");
      } else {
         RES *res = GetResWithName(R_CLIENT, lc->str);
         if (res == NULL) {
            scan_err3(lc, _("Could not find config Resource %s referenced on line %d : %s\n"),
                      lc->str, lc->line_no, lc->line);
         }

         ((RUNSCRIPT*) item->value)->set_target(lc->str);
      }
   }
   scan_to_eol(lc);
}
