gt_simpleexactselfmatchstore(void *info,
                                        const GtEncseq *encseq,
                                        unsigned long len,
                                        unsigned long pos1,
                                        unsigned long pos2,
                                        GT_UNUSED GtError *err)
{
  unsigned long distance;
  RepeatInfo *repeatinfo = (RepeatInfo *) info;

  gt_error_check(err);
  if (pos1 > pos2)
  {
    unsigned long tmp = pos1;
    pos1 = pos2;
    pos2 = tmp;
  }
  if (repeatinfo->ltrsearchseqrange.start > 0 ||
      repeatinfo->ltrsearchseqrange.end > 0)
  {
    if (pos1 < repeatinfo->ltrsearchseqrange.start  ||
        pos2 + len - 1 > repeatinfo->ltrsearchseqrange.end)
    {
      return 0;
    }
  }
  distance = pos2 - pos1;

  if (len <= repeatinfo->lmax && repeatinfo->dmin <= distance
                              && distance <= repeatinfo->dmax)
  {
    const unsigned long seqnum1 = gt_encseq_seqnum(encseq,pos1);
    const unsigned long seqnum2 = gt_encseq_seqnum(encseq,pos2);

    if (seqnum1 == seqnum2)
    {
      Repeat *nextfreerepeatptr;

      GT_GETNEXTFREEINARRAY(nextfreerepeatptr,&repeatinfo->repeats,Repeat,32);
      nextfreerepeatptr->pos1 = pos1;
      nextfreerepeatptr->offset = distance;
      nextfreerepeatptr->len = len;
      nextfreerepeatptr->contignumber = seqnum1;
    }
  }
  return 0;
}
