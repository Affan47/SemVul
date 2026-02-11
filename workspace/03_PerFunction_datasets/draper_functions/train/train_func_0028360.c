replace_equi(chain_list* abl)
{
   chain_list* head;
   equi_list* equi;

   if (ABL_ATOM(abl)) {
      for (equi=EQUI; equi; equi=equi->NEXT) {
         if (equi->NAME==ABL_ATOM_VALUE(abl)) {

            freeablexpr(abl);
            abl=dupablexpr(equi->ABL);

            if (ABL_ARITY(equi->ABL)!=0) put_arity_abl(abl);
            return abl;
         }
      }
      return abl;
   }

   head=abl;
   for (abl=ABL_CDR(head); abl; abl=ABL_CDR(abl)) {
      ABL_CAR_L(abl)=replace_equi(ABL_CAR(abl));
   }

   return head;
}
