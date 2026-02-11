gt_packedindexuniqueforward(const BWTSeq *bwtSeq,
                                          const GtUchar *qstart,
                                          const GtUchar *qend)
{
  GtUchar cc;
  const GtUchar *qptr;
  struct matchBound bwtbound;
  GtUlongPair seqpospair;
  Symbol curSym;
  const MRAEnc *alphabet;

  gt_assert(bwtSeq && qstart);
  alphabet = BWTSeqGetAlphabet(bwtSeq);
  qptr = qstart;
  cc = *qptr++;
#undef SKDEBUG
#ifdef SKDEBUG
  printf("# start cc=%u\n",cc);
#endif
  if (ISSPECIAL(cc))
  {
    return 0;
  }
  curSym = MRAEncMapSymbol(alphabet, cc);
  bwtbound.start = bwtSeq->count[curSym];
  bwtbound.end = bwtSeq->count[curSym+1];
#ifdef SKDEBUG
  printf("# bounds=%lu,%lu = %lu"
          "occurrences\n",
         bwtbound.start,
         bwtbound.end,
         bwtbound.end - bwtbound.start);
#endif
  while (qptr < qend && bwtbound.start + 1 < bwtbound.end)
  {
    cc = *qptr;
#ifdef SKDEBUG
    printf("# cc=%u\n",cc);
#endif
    if (ISSPECIAL (cc))
    {
      return 0;
    }
    curSym = MRAEncMapSymbol(alphabet, cc);
    seqpospair = BWTSeqTransformedPosPairOcc(bwtSeq, curSym,
                                             bwtbound.start,bwtbound.end);
    bwtbound.start = bwtSeq->count[curSym] + seqpospair.a;
    bwtbound.end = bwtSeq->count[curSym] + seqpospair.b;
#ifdef SKDEBUG
    printf("# bounds=%lu,%lu = %lu"
            "occurrences\n",
           bwtbound.start,
           bwtbound.end,
           bwtbound.end - bwtbound.start);
#endif
    qptr++;
  }
  if (bwtbound.start + 1 == bwtbound.end)
  {
    return (unsigned long) (qptr - qstart);
  }
  return 0;
}
