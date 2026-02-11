lsp_weight_quant(spx_word16_t *x, spx_word16_t *weight, const signed char *cdbk, int nbVec, int nbDim)
{
   int i,j;
   spx_word32_t dist;
   spx_word16_t tmp;
   spx_word32_t best_dist=VERY_LARGE32;
   int best_id=0;
   const signed char *ptr=cdbk;
   for (i=0;i<nbVec;i++)
   {
      dist=0;
      for (j=0;j<nbDim;j++)
      {
         tmp=SUB16(x[j],SHL16((spx_word16_t)*ptr++,5));
         dist=MAC16_32_Q15(dist,weight[j],MULT16_16(tmp,tmp));
      }
      if (dist<best_dist)
      {
         best_dist=dist;
         best_id=i;
      }
   }

   for (j=0;j<nbDim;j++)
      x[j] = SUB16(x[j],SHL16((spx_word16_t)cdbk[best_id*nbDim+j],5));
   return best_id;
}
