gt_sain_compare_suffixes(const GtSainseq *sainseq,
                                    unsigned long start1,
                                    unsigned long start2)
{
  gt_assert(start1 <= sainseq->totallength &&
            start2 <= sainseq->totallength &&
            start1 != start2);

  while (true)
  {
    unsigned long cc1, cc2;

    if (start1 == sainseq->totallength)
    {
      gt_assert(start1 > start2);
      return 1;
    }
    if (start2 == sainseq->totallength)
    {
      gt_assert(start1 < start2);
      return -1;
    }
    cc1 = gt_sainseq_getchar(sainseq,start1);
    cc2 = gt_sainseq_getchar(sainseq,start2);
    if (cc1 < cc2)
    {
      return -1;
    }
    if (cc1 > cc2)
    {
      return 1;
    }
    start1++;
    start2++;
  }
}
