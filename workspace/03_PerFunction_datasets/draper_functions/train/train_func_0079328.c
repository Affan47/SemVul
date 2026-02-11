fights_(integer h, logical flg)
{


   const integer smin = 2;
   const integer smax = 7;


   integer ret_val;

   ret_val = smin + ((smax - smin) * advs_1.ascore[h - 1] + state_1.mxscor /
         2) / state_1.mxscor;
   if (flg) {
      ret_val += advs_1.astren[h - 1];
   }
   return ret_val;
}
