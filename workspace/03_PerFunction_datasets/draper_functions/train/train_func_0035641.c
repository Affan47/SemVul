gt_strgraph_longest_read(GtStrgraph *strgraph)
{
  if (strgraph->fixlen > 0)
  {
    return strgraph->fixlen;
  }
  else
  {
    GtStrgraphLength seqlen, maxseqlen;
    GtStrgraphVnum i;

    gt_assert(strgraph->encseq != NULL);
    maxseqlen = 0;
    for (i = 0; i < GT_STRGRAPH_NOFREADS(strgraph); i++)
    {
      seqlen = (GtStrgraphLength)gt_encseq_seqlength(strgraph->encseq,
          (unsigned long)i);
      if (seqlen > maxseqlen)
        maxseqlen = seqlen;
    }
    gt_assert(maxseqlen > 0);
    gt_assert(sizeof (GtStrgraphLength) >= sizeof (unsigned long) ||
        maxseqlen <= GT_STRGRAPH_LENGTH_MAX);
    return maxseqlen;
  }
}
