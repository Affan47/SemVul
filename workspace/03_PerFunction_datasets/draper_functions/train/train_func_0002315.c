sse_alloc_vjd_deck(int L, int i, int j, int x)
{
  int status;
  int     jp;
  int     sW;
  int     vecs = 0;
  sse_deck_t *tmp;
  ESL_DPRINTF3(("alloc_vjd_deck : %.4f\n", size_vjd_deck(L,i,j)));
  ESL_ALLOC(tmp, sizeof(sse_deck_t));
  ESL_ALLOC(tmp->vec, sizeof(__m128 *) * (L+1));
  ESL_ALLOC(tmp->ivec, sizeof(__m128i *) * (L+1));
  for (jp = 0; jp <= j-i+1; jp++) {
    sW = jp/x + 1;
    vecs += sW;
  }
  ESL_ALLOC(tmp->mem , sizeof(__m128  ) * vecs + 15);
  for (jp = 0;   jp < i-1;    jp++) tmp->vec[jp]     = NULL;
  for (jp = j+1; jp <= L;     jp++) tmp->vec[jp]     = NULL;
  tmp->vec[i-1] = (__m128 *) (((unsigned long int) tmp->mem + 15) & (~0xf));
  for (jp = 1;   jp <= j-i+1; jp++) {
    sW = (jp-1)/x + 1;
    tmp->vec[jp+i-1] = tmp->vec[jp+i-2] + sW;
  }
  for (jp = 0; jp <=L; jp++) { tmp->ivec[jp] = (__m128i *) tmp->vec[jp]; }
  return tmp;
 ERROR:
  cm_Fail("Memory allocation error.");
  return NULL;
}
