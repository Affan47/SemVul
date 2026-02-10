gt_nextEnumpatterniterator(unsigned long *patternlen,
                                       Enumpatterniterator *epi)
{
  unsigned long start;
  unsigned long j;
  GtUchar cc;

  if (epi->minpatternlen == epi->maxpatternlen)
  {
    *patternlen = epi->minpatternlen;
  } else
  {
    *patternlen = (unsigned long) (epi->minpatternlen +
                                   (random() %
                                      (epi->maxpatternlen -
                                       epi->minpatternlen+1)));
  }
  start =
        (unsigned long) (random() % (epi->totallength - *patternlen));
  gt_assert(start < (unsigned long) (epi->totallength - *patternlen));
  if (epi->esr == NULL) {
    epi->esr = gt_encseq_create_reader_with_readmode(epi->sampleencseq,
                                          GT_READMODE_FORWARD,
                                          start);
  } else {
    gt_encseq_reader_reinit_with_readmode(epi->esr, epi->sampleencseq,
                                          GT_READMODE_FORWARD,
                                          start);
  }

  for (j=0; j<*patternlen; j++)
  {
    cc = gt_encseq_reader_next_encoded_char(epi->esr);
    if (ISSPECIAL(cc))
    {
      cc = (GtUchar) (random() % epi->alphasize);
    }
    epi->patternspace[j] = cc;
  }
  if (epi->samplecount & 1)
  {
    reversesequenceinplace(epi->patternspace,*patternlen);
  }
  epi->samplecount++;
  epi->patternstat[*patternlen]++;
  return epi->patternspace;
}
