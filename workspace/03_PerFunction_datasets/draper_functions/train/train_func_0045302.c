propagate_loins_delay(loins_list *loins)
{
   locon_list* locon;


   for (locon=loins->LOCON; locon; locon=locon->NEXT) {
      if (locon->DIRECTION==UNKNOWN) {
         fprintf(stderr,"BEH: 'linkage %s' in figure '%s' isn't accepted\n",
         locon->NAME,loins->INSNAME);
         autexit(1);
      }
      if (locon->DIRECTION==IN || locon->DIRECTION==INOUT || locon->DIRECTION==TRANSCV)
         propagate_losig_delay(locon->SIG);
   }


   for (locon=loins->LOCON; locon; locon=locon->NEXT) {
      if (locon->DIRECTION==IN) continue;
      propagate_losig_delay(locon->SIG);
   }
}
