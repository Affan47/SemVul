search_name(char* name, befig_list* befig)
{
   bereg_list* bereg;
   beaux_list* beaux;
   bebux_list* bebux;
   biabl_list* biabl;


   for (beaux=befig->BEAUX; beaux; beaux=beaux->NEXT) {
      if (beaux->NAME!=name) continue;
      search_abl(beaux->ABL,befig);
      eval_delay(beaux->NAME,beaux->ABL);
      return;
   }

   for (bebux=befig->BEBUX; bebux; bebux=bebux->NEXT) {
      if (bebux->NAME!=name) continue;
      for (biabl=bebux->BIABL; biabl; biabl=biabl->NEXT) {
         search_abl(biabl->CNDABL,befig);
         search_abl(biabl->VALABL,befig);
      }
      eval_bus(bebux->NAME,bebux->BIABL);
      return;
   }

   for (bereg=befig->BEREG; bereg; bereg=bereg->NEXT) {
      if (bereg->NAME!=name) continue;
      for (biabl=bereg->BIABL; biabl; biabl=biabl->NEXT) {
         search_abl(biabl->CNDABL,befig);
         if (!getptype(biabl->USER,ABL_STABLE)) {
            search_abl(biabl->VALABL,befig);
         }
      }


      eval_reg(bereg->NAME,bereg->BIABL);
      return;
   }


   fprintf(stderr,"search_name: %s unknown\n",name);
   exit(1);
}
