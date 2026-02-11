constructsarrandrunmaxpairs(
                 Substringmatchinfo *ssi,
                 GtReadmode readmode,
                 unsigned int prefixlength,
                 unsigned int numofparts,
                 unsigned long maximumspace,
                 GtTimer *sfxprogress,
                 bool withprogressbar,
                 GT_UNUSED GtLogger *logger,
                 GtError *err)
{
  const GtSuffixsortspace *suffixsortspace;
  unsigned long numberofsuffixes;
  bool haserr = false;
  Sfxiterator *sfi;
  bool specialsuffixes = false;

  Sfxstrategy sfxstrategy;

  defaultsfxstrategy(&sfxstrategy,
                     gt_encseq_bitwise_cmp_ok(ssi->encseq) ? false : true);
  sfi = gt_Sfxiterator_new(ssi->encseq,
                           readmode,
                           prefixlength,
                           numofparts,
                           maximumspace,
                           &sfxstrategy,
                           sfxprogress,
                           withprogressbar,
                           NULL,
                           err);
  if (sfi == NULL)
  {
    haserr = true;
  } else
  {
    Sequentialsuffixarrayreader *ssar = NULL;
    bool firstpage = true;

    ssar = gt_newSequentialsuffixarrayreaderfromRAM(ssi->encseq,
                                                    readmode);
    while (true)
    {
      suffixsortspace = gt_Sfxiterator_next(&numberofsuffixes,&specialsuffixes,
                                            sfi);
      if (suffixsortspace == NULL || specialsuffixes)
      {
        break;
      }
      gt_updateSequentialsuffixarrayreaderfromRAM(
               ssar,
               (const ESASuffixptr *)
               gt_suffixsortspace_ulong_get(suffixsortspace),
               firstpage,
               numberofsuffixes);
      firstpage = false;
      if (gt_enumeratemaxpairs(ssar,
                               ssi->encseq,
                               readmode,
                               ssi->minlength,
                               ssi->processmaxpairs,
                               ssi->processmaxpairsinfo,
                               err) != 0)
      {
        haserr = true;
      }
    }
    if (ssar != NULL)
    {
      gt_freeSequentialsuffixarrayreader(&ssar);
    }
  }
  if (gt_Sfxiterator_delete(sfi,err) != 0)
  {
    haserr = true;
  }
  return haserr ? -1 : 0;
}
