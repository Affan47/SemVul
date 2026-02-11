newsignal()
{
   signal_list* new;
   int i;

   if (!HEAD) {
      HEAD=mbkalloc(BLOCK*sizeof(signal_list));
      BLOCK_LIST=addchain(BLOCK_LIST,HEAD);
      new=HEAD;
      for (i = 1; i < BLOCK; i++) {
         new->NEXT = new + 1;
         new++;
      }
      new->NEXT = NULL;
   }

   new=HEAD;
   HEAD=HEAD->NEXT;


   new->NEXT=NULL;
   new->BEAUX=NULL;
   new->C=DEFAULT_CAPACITANCE;
   new->T=DEFAULT_DELAY;
   new->DELAY_SET=0;
   return new;
}
