gth_backtrace_path_determine_cutoffs(GthBacktracePath *bp,
                                          GthCutoffmode leadcutoffsmode,
                                          GthCutoffmode termcutoffsmode,
                                          unsigned long cutoffsminexonlen)
{
  gt_assert(bp);

  gt_assert(bp->alphatype == DNA_ALPHA || bp->alphatype == PROTEIN_ALPHA);
  memset(&bp->cutoffs, 0, sizeof bp->cutoffs);
  determine_cutoffs(bp, leadcutoffsmode, termcutoffsmode, cutoffsminexonlen);
}
