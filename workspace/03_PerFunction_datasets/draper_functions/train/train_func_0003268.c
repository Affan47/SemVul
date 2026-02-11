gt_randomcodes_correct_process_kmer_itv(
    const unsigned long *suffixes,
    unsigned long nofsuffixes,
    GtRandomcodesCorrectData *cdata)
{
  unsigned int i, c = cdata->c;
  cdata->nofkmeritvs++;
  cdata->nofkmers += nofsuffixes;
  if (nofsuffixes < (unsigned long)cdata->c)
  {
    cdata->alltrusted = false;
    c = (unsigned int)nofsuffixes;
  }
  for (i = 0; i < c; i++)
  {
    (cdata->kpositions + cdata->currentchar * cdata->c)[i] = suffixes[i];
  }
  cdata->count[cdata->currentchar] = (unsigned int)nofsuffixes;
  cdata->currentchar++;
}
