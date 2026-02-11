lDelSubUlong(lListElem *ep, int nm, lUlong val, int snm)
{
   int ret, sublist_pos;

   DENTER(CULL_LAYER, "lDelSubUlong");


   sublist_pos = lGetPosViaElem(ep, snm, SGE_DO_ABORT);

   ret = lDelElemUlong(&(ep->cont[sublist_pos].glp), nm, val);


   if (ret == 1) {
      sge_bitfield_set(&(ep->changed), sublist_pos);
   }

   DEXIT;
   return ret;
}
