shu_compute_leaf_edge_contrib(GtBUstate_shulen *state,
                                          const unsigned long *fathernumdist,
                                          unsigned long gnum,
                                          unsigned long fatherdepth)
{
  unsigned long idx;
#ifdef GENOMEDIFF_PAPER_IMPL
  gt_assert(state->leafdist != NULL);
  for (idx = 0; idx < state->numofdbfiles; idx++)
  {
    state->leafdist[idx] = 0;
  }
  state->leafdist[gnum] = 1UL;
  cartproduct_shulen(state,fatherdepth,fathernumdist,state->leafdist);
  cartproduct_shulen(state,fatherdepth,state->leafdist,fathernumdist);
#else
  for (idx = 0; idx < state->numofdbfiles; idx++)
  {
    if (idx != gnum && fathernumdist[idx] > 0)
    {
      contribute_shulen(__LINE__,
                        state->shulengthdist,
                        idx,
                        gnum,
                        1UL,
                        fatherdepth+1);
      if (fathernumdist[gnum] == 0)
      {
        contribute_shulen(__LINE__,
                          state->shulengthdist,
                          gnum,
                          idx,
                          fathernumdist[idx],
                          fatherdepth + 1);
      }
    }
  }
#endif
}
