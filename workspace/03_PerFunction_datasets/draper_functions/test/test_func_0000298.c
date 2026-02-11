find_stable(chain_list* abl)
{
   char* ck=NULL, *new;


   if (ABL_ATOM(abl)) return NULL;

   if (ABL_OPER(abl)==ABL_STABLE) {
      return ABL_ATOM_VALUE(ABL_CADR(abl));
   }
   for (abl=ABL_CDR(abl); abl; abl=ABL_CDR(abl)) {
      new=find_stable(ABL_CAR(abl));
      if (new) {
         if (ck) {
            BEH_ERROR=1;
            return ck;
         }
         ck=new;
      }
   }


   return ck;
}
