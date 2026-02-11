gt_loadvoidBWTSeqForSA(const char *indexname,
                                bool withpckbt,
                                GtError *err)
{
  BWTSeq *bwtseq = NULL;
  bool haserr = false;
  GtEncseqMetadata *emd;
  GtAlphabet *alphabet;

  emd = gt_encseq_metadata_new(indexname, err);
  if (emd == NULL) {
    gt_assert(gt_error_is_set(err));
    haserr = true;
  }
  if (!haserr) {
    alphabet = gt_encseq_metadata_alphabet(emd);
    if (alphabet == NULL)
    {
      gt_assert(gt_error_is_set(err));
      haserr = true;
    }
  }
  if (!haserr)
  {
    bwtseq = gt_loadBWTSeqForSA(indexname,
                                BWT_ON_BLOCK_ENC,
                                BWTDEFOPT_MULTI_QUERY,
                                alphabet,
                                err);
    if (bwtseq == NULL)
    {
      gt_assert(gt_error_is_set(err));
      haserr = true;
    }
  }
  if (!haserr)
  {
    if (withpckbt && gt_pckbuckettable_exists(indexname))
    {
      unsigned int numofchars = gt_alphabet_num_of_chars(alphabet);
      bwtseq->pckbuckettable = gt_pckbuckettable_map(indexname,numofchars,err);
      if (bwtseq->pckbuckettable == NULL)
      {
        gt_assert(gt_error_is_set(err));
        haserr = true;
      }
    } else
    {
      bwtseq->pckbuckettable = NULL;
    }
  }
  gt_encseq_metadata_delete(emd);
  if (haserr && bwtseq != NULL)
  {
    gt_deletevoidBWTSeq((FMindex *) bwtseq);
    bwtseq = NULL;
  }
  return haserr ? NULL : (FMindex *) bwtseq;
}
