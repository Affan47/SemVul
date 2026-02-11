LeftMarginalScore_reproduce_i27(const ESL_ALPHABET *abc, float *esc, ESL_DSQ dres)
{
   float *left = NULL;
   int status;
   ESL_ALLOC(left,  (sizeof(float) * (abc->K+1)));
   int i;
   float sc;

   if (dres < abc->K)
   {
     sc = esl_vec_FLogSum(&(esc[dres*abc->K]),abc->K);
     sc -= sreLOG2(abc->K);
   }
   else
   {
      esl_vec_FSet(left, abc->K, 0.);
      esl_abc_FCount(abc, left, dres, 1.);

      sc = 0.;
      for (i = 0; i < abc->K; i++)
      {
	sc += esl_vec_FLogSum(&(esc[i*abc->K]),abc->K)*left[i];
	sc -= sreLOG2(abc->K)*left[i];
      }
   }

   free(left);

   return sc;

 ERROR:
  cm_Fail("Memory allocation error.");
  return 0.0;
}
