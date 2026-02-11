gt_chain2dim_insertintodict(bool addterminal,
                                        const GtChain2Dimmatchtable *matchtable,
                                        GtChain2DimMatchstore *matchstore,
                                        GtChain2DimMatchpoint *qmatch2)
{
  GtChain2DimMatchpoint *retval2;
  bool nodecreated;

  retval2 = (GtChain2DimMatchpoint *) gt_rbtree_search(matchstore->dictroot,
                                                       qmatch2,
                                                       &nodecreated);
  gt_assert(retval2 != NULL);
  if (!nodecreated)
  {
    if (gt_chain2dim_evalpriority(addterminal,matchtable,FRAGIDENT(retval2)) <
        gt_chain2dim_evalpriority(addterminal,matchtable,FRAGIDENT(qmatch2)))
    {
      gt_assert(retval2->fpposition == qmatch2->fpposition);
      retval2->fpident = qmatch2->fpident;
    }
  }
}
