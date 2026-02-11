mlpgChol(PStreamChol *pst)
{
   register int m;


   for (m = 0; m <= pst->order; m++) {
       calc_R_and_r(pst, m);
       Choleski(pst);
       Choleski_forward(pst);
       Choleski_backward(pst, m);
   }

   return;
}
