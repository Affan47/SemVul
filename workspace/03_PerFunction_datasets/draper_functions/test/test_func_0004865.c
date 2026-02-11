HTS_PStream_forward_substitution(HTS_PStream * pst)
{
   size_t t, i;

   for (t = 0; t < pst->length; t++) {
      pst->sm.g[t] = pst->sm.wum[t];
      for (i = 1; (i < pst->width) && (t >= i); i++)
         pst->sm.g[t] -= pst->sm.wuw[t - i][i] * pst->sm.g[t - i];
   }
}
