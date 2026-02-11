gt_newSfxInterfaceWithReaders(GtReadmode readmode,
                              unsigned int prefixlength,
                              unsigned int numofparts,
                              unsigned long maximumspace,
                              const Sfxstrategy *sfxstrategy,
                              size_t numReaders,
                              enum sfxDataRequest readerRequests[],
                              SeqDataReader readers[],
                              const GtEncseq *encseq,
                              GtTimer *sfxprogress,
                              bool withprogressbar,
                              unsigned long length,
                              GtLogger *verbosity, GtError *err)
{
  sfxInterface *sfxi = NULL;
  size_t idx;

  gt_error_check(err);
  sfxi = gt_calloc(1, sizeof (*sfxi));
  {
    RandomSeqAccessor origSeqAccess = { gt_SfxIGetOrigSeq, sfxi };
    initSASeqSrc(&sfxi->baseClass, length, SfxIBaseRequest2XltorFunc, NULL,
                 SfxIBaseGetRot0Pos, SfxIBaseGetSeqStats,
                 origSeqAccess, gt_deleteSfxInterfaceBase, SfxIBaseNewMRAEnc,
                 SfxIGenerate, sfxi);
  }
  sfxi->readmode = readmode;
  sfxi->encseq = encseq;
  sfxi->alpha = gt_encseq_alphabet(encseq);
  sfxi->stats = newSeqStatsFromCharDist(encseq,sfxi->alpha, length);
  if (!(sfxi->sfi = gt_Sfxiterator_new(encseq,
                                       readmode,
                                       prefixlength,
                                       numofparts,
                                       maximumspace,
                                       sfxstrategy,
                                       sfxprogress,
                                       withprogressbar,
                                       verbosity,
                                       err)))
  {
    gt_newSfxInterfaceWithReadersErrRet();
  }
  sfxi->rot0Pos.defined = false;

  sfxi->lastGeneratedStart = sfxi->lastGeneratedLen = 0;
  sfxi->lastGeneratedSufTabSegment = NULL;

  for (idx = 0; idx < numReaders; ++idx)
  {
    readers[idx] = gt_SfxIRegisterReader(sfxi, readerRequests[idx]);
    if (!readers[idx].readData)
    {
      gt_newSfxInterfaceWithReadersErrRet();
    }
  }
  return sfxi;
}
