gt_encseq_has_twobitencoding(const GtEncseq *encseq)
{
  gt_assert(encseq != NULL);
  return (encseq->accesstype_via_utables ||
          encseq->sat >= GT_ACCESS_TYPE_EQUALLENGTH ||
          encseq->sat == GT_ACCESS_TYPE_BITACCESS) ? true : false;
}
