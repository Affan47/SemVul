gt_firstcodes_insert_runkmerscan(const GtEncseq *encseq,
                                      unsigned int kmersize,
                                      unsigned int minmatchlength,
                                      GtCodeposbuffer *buf)
{
  const GtTwobitencoding *twobitencoding
    = gt_encseq_twobitencoding_export(encseq);
  unsigned long totallength, maxunitindex, numofsequences;

  gt_assert(minmatchlength>=kmersize);
  if (gt_encseq_is_mirrored(encseq))
  {
    totallength = (gt_encseq_total_length(encseq)-1)/2;
  } else
  {
    totallength = gt_encseq_total_length(encseq);
  }
  numofsequences = gt_encseq_num_of_sequences(encseq);
  maxunitindex = gt_unitsoftwobitencoding(totallength) - 1;
  if (gt_encseq_accesstype_get(encseq) == GT_ACCESS_TYPE_EQUALLENGTH)
  {
    unsigned long equallength = gt_encseq_equallength(encseq);

    gt_assert(equallength >= (unsigned long) kmersize);
    gt_firstcodes_insert_kmerscan_eqlen(twobitencoding,
                                        equallength,
                                        totallength,
                                        numofsequences,
                                        maxunitindex,
                                        kmersize,
                                        minmatchlength,
                                        buf);
  } else
  {
    gt_firstcodes_insert_kmerscan(encseq,
                                  twobitencoding,
                                  totallength,
                                  numofsequences,
                                  maxunitindex,
                                  kmersize,
                                  minmatchlength,
                                  buf);
  }
}
