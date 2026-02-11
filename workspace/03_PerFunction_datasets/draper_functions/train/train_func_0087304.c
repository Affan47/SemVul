wchmm_fbs_free(RecogProcess *r)
{
  StackDecode *dwrk;
  dwrk = &(r->pass2);

  if (r->lmtype == LM_PROB && r->lm->ngram) {
    free(dwrk->cnword);
    free(dwrk->cnwordrev);
    dwrk->cnword = dwrk->cnwordrev = NULL;
  }

#ifdef CONFIDENVE_MEASURE
#ifdef CM_MULTIPLE_ALPHA
  if (dwrk->cmsumlist) {
    free(dwrk->cmsumlist);
    dwrk->cmsumlist = NULL;
  }
#endif
#ifdef CM_NBEST;
  if (dwrk->sentcm) {
    free(dwrk->sentcm);
    dwrk->sentcm = NULL;
  }
  if (dwrk->wordcm) {
    free(dwrk->wordcm);
    dwrk->wordcm = NULL;
  }
#endif
#endif
}
