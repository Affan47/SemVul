vilstr_(integer v)
{

   integer ret_val, i__1, i__2, i__3;


   integer i;

   ret_val = objcts_1.ocapac[v - 1];
   if (ret_val <= 0) {
      return ret_val;
   }
   if (v == oindex_1.thief && findex_1.thfenf) {
      findex_1.thfenf = FALSE_;

      ret_val = min(ret_val,2);

   }
   for (i = 1; i <= vill_1.vlnt; ++i) {

      if (vill_1.villns[i - 1] == v && prsvec_1.prsi == vill_1.vbest[i - 1]
         ) {

         i__2 = 1, i__3 = ret_val - 1;
         ret_val = max(i__2,i__3);
      }
   }
   return ret_val;
}
