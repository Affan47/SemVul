count_instance(lofig_list* lofig)
{
   ptype_list *ptype, *temp=NULL, *inst=NULL, *low, *pred, *pred_low;
   loins_list* loins;

   if (!lofig) {
      fprintf(stderr,"count_instance: NULL pointer\n");
      autexit(1);
   }

   NUM_INS=0;

   for (loins=lofig->LOINS; loins; loins=loins->NEXT) {
      for (ptype=temp; ptype; ptype=ptype->NEXT) {
         if ((char*)ptype->DATA==loins->FIGNAME) break;
      }
      if (ptype) ptype->TYPE++;
      else temp=addptype(temp,1,loins->FIGNAME);
      NUM_INS++;
   }


   while (temp) {
      low=temp;
      pred_low=NULL;
      pred=temp;


      for (ptype=temp->NEXT; ptype; ptype=ptype->NEXT) {
         if (ptype->TYPE<low->TYPE) {
            pred_low=pred;
            low=ptype;
         }
         pred=ptype;
      }


      if (!pred_low) temp=low->NEXT;
      else pred_low->NEXT=low->NEXT;

      low->NEXT=inst;
      inst=low;
   }

   return inst;
}
