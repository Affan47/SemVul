gt_seqnumrelpos_encode(const GtSeqnumrelpos *snrp,
                                     unsigned long seqnum,
                                        unsigned long relpos)
{
  gt_assert(relpos <= snrp->relposmask);
  return (seqnum << snrp->bitsforrelpos) | relpos;
}
