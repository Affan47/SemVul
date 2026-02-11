average_capacitance(befig_list *befig)
{
   bereg_list* bereg;
   bebux_list* bebux;
   beaux_list* beaux;
   bepor_list* bepor;
   char* name;
   float capa;


   for (beaux=befig->BEAUX; beaux; beaux=beaux->NEXT) {
      name=getoppositename(beaux->NAME);
      capa=getcapacitance(beaux->NAME);
      capa+=getcapacitance(name);
      capa=capa/2;
      putcapacitance(beaux->NAME,capa);
      putcapacitance(name,capa);
   }

   for (bereg=befig->BEREG; bereg; bereg=bereg->NEXT) {
      name=getoppositename(bereg->NAME);
      capa=getcapacitance(bereg->NAME);
      capa+=getcapacitance(name);
      capa=capa/2;
      putcapacitance(bereg->NAME,capa);
      putcapacitance(name,capa);
   }

   for (bebux=befig->BEBUX; bebux; bebux=bebux->NEXT) {
      name=getoppositename(bebux->NAME);
      capa=getcapacitance(bebux->NAME);
      capa+=getcapacitance(name);
      capa=capa/2;
      putcapacitance(bebux->NAME,capa);
      putcapacitance(name,capa);
   }

   for (bepor=befig->BEPOR; bepor; bepor=bepor->NEXT) {

      if (isvss(bepor->NAME) || isvdd(bepor->NAME)) continue;
      switch (bepor->DIRECTION) {case OUT: case TRISTATE: continue;}
      name=getoppositename(bepor->NAME);
      capa=getcapacitance(bepor->NAME);
      capa+=getcapacitance(name);
      capa=capa/2;
      putcapacitance(bepor->NAME,capa);
      putcapacitance(name,capa);
   }

}
