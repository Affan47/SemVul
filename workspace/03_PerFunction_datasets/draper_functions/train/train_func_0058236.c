gt_encseq_unmirror(GtEncseq *encseq)
{
  gt_assert(encseq && encseq->hasmirror);
  encseq->hasmirror = false;
  encseq->logicalnumofdbsequences = encseq->numofdbsequences;
  encseq->logicaltotallength = encseq->totallength;
}
