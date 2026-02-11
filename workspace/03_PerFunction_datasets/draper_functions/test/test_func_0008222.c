test5(
   procA *p,
   H_UINT offs,
   H_UINT tid)
{
   H_UINT8 * dp;
   H_UINT j, k, max, tau, Z_tau;


   if (0 != (p->options & A_CYCLE)) {
      j = p->options & A_CYCLE;
      if (j==0 || ((tid-1)/5 % j)!=0) {
         p->results[tid++].testResult = 0xff00;
         p->testRun = tid;
         p->testState = TEST_DONE;
         return offs;
         }
      }


   dp = (H_UINT8 *) p->chain5;
   for (max = k = 0,tau=1;tau<=TEST5_LENGTH;tau++){
      Z_tau = abs(test5XOR(dp, tau) - 2500);
      if (Z_tau > max) {
         max = Z_tau;
         k = tau - 1;
         }
      }
   dp += TEST5_LENGTH/8;
   Z_tau = test5XOR(dp, k + 1);
   j = 5<<8;
   if (( Z_tau <= 2326) || ( Z_tau >= 2674))
      j  |= 1;

   p->results[tid].testResult = j;
   p->results[tid++].finalValue = Z_tau;
   p->testRun = tid;
   p->testState = TEST_DONE;
   return offs;
}
