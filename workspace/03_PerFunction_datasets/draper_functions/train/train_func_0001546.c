parse_noopt(
char **sp,
const char *shortopt,
const char *longopt,
lList **ppcmdline,
lList **alpp
) {

   DENTER (TOP_LAYER, "parse_noopt");

   if ( (!strcmp(shortopt, *sp)) || (longopt && !strcmp(longopt, *sp)) ) {
      if(!lGetElemStr(*ppcmdline, SPA_switch, shortopt)) {
         sge_add_noarg(ppcmdline, 0, shortopt, NULL);
      }
      sp++;
   }
   DEXIT;
   return sp;
}
