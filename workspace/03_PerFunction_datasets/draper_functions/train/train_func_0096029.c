gt_chain2dim_retrace_previousinchain(GtChain2Dim *chain,
                                   const GtChain2Dimmatchtable *matchtable,
                                   unsigned long retracestart)
{
  unsigned long matchnum, lengthofchain;

  chain->storedinreverseorder = false;
  for (lengthofchain = 0, matchnum = retracestart;
       matchnum != GT_CHAIN2DIM_UNDEFPREVIOUS; lengthofchain++)
  {

    matchnum = matchtable->matches[matchnum].previousinchain;
  }
  GT_MINARRAYSPACE(&chain->chainedmatches,GtChain2Dimref,lengthofchain);
  chain->chainedmatches.nextfreeGtChain2Dimref = lengthofchain;
  for (matchnum = retracestart;
       matchnum != GT_CHAIN2DIM_UNDEFPREVIOUS;

       matchnum = matchtable->matches[matchnum].previousinchain)
  {
    gt_assert(lengthofchain > 0);
    lengthofchain--;
    chain->chainedmatches.spaceGtChain2Dimref[lengthofchain] = matchnum;
  }
  gt_assert(lengthofchain == 0);
}
