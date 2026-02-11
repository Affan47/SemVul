flatArray(const int size, double* vect)
{
   const int index = seq;
   long seed1 = table[index][0];
   long seed2 = table[index][1];
   int k1, k2;
   register int i;

   for (i=0; i<size; ++i)
   {
     k1 = (int)(seed1/ecuyer_b);
     k2 = (int)(seed2/ecuyer_e);

     seed1 = ecuyer_a*(seed1-k1*ecuyer_b)-k1*ecuyer_c;
     if (seed1 < 0) seed1 += shift1;
     seed2 = ecuyer_d*(seed2-k2*ecuyer_e)-k2*ecuyer_f;
     if (seed2 < 0) seed2 += shift2;

     long diff = seed1-seed2;
     if (diff <= 0) diff += (shift1-1);

     vect[i] = (double)(diff*prec);
   }
   table[index][0] = seed1;
   table[index][1] = seed2;
}
