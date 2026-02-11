gt_chain2dim_overlapping(const GtChain2Dimmatchtable *matchtable,
                                     unsigned long i,
                                     unsigned long j)
{
  return (GT_CHAIN2DIM_GETSTOREDENDPOINT(0,i)
            >= GT_CHAIN2DIM_GETSTOREDSTARTPOINT(0,j) ||
          GT_CHAIN2DIM_GETSTOREDENDPOINT(1,i)
            >= GT_CHAIN2DIM_GETSTOREDSTARTPOINT(1,j)) ? true : false;
}
