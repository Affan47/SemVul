mdf_adjust_prop(const spx_word32_t *W, int N, int M, int P, spx_word16_t *prop)
{
   int i, j, p;
   spx_word16_t max_sum = 1;
   spx_word32_t prop_sum = 1;
   for (i=0;i<M;i++)
   {
      spx_word32_t tmp = 1;
      for (p=0;p<P;p++)
         for (j=0;j<N;j++)
            tmp += MULT16_16(EXTRACT16(SHR32(W[p*N*M + i*N+j],18)), EXTRACT16(SHR32(W[p*N*M + i*N+j],18)));
#ifdef FIXED_POINT

      tmp = MIN32(ABS32(tmp), 536870912);
#endif
      prop[i] = spx_sqrt(tmp);
      if (prop[i] > max_sum)
         max_sum = prop[i];
   }
   for (i=0;i<M;i++)
   {
      prop[i] += MULT16_16_Q15(QCONST16(.1f,15),max_sum);
      prop_sum += EXTEND32(prop[i]);
   }
   for (i=0;i<M;i++)
   {
      prop[i] = DIV32(MULT16_16(QCONST16(.99f,15), prop[i]),prop_sum);

   }

}
