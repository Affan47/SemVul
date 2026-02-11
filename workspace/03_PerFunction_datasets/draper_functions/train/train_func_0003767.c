format_register(befig_list* befig)
{
   bereg_list* bereg;

   if (!befig) {
      fprintf(stderr,"format_register: NULL pointer\n");
      autexit(1);
   }

   BEH_ERROR=0;

   for (bereg=befig->BEREG; bereg; bereg=bereg->NEXT) {
      if (!loc_format_register(bereg)) return 0;
   }

   return 1;
}
