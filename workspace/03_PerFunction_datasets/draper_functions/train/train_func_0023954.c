storematch(void *info,const GtIdxMatch *match)
{
  Storematchinfo *storematch = (Storematchinfo *) info;
  unsigned long seqnum;

  if (match->dbabsolute)
  {
    seqnum = gt_encseq_seqnum(storematch->encseq,
                                           match->dbstartpos);
  } else
  {
    seqnum = match->dbseqnum;
  }
  if (!GT_ISIBITSET(storematch->hasmatch,seqnum))
  {
    GT_SETIBIT(storematch->hasmatch,seqnum);
  }
}
