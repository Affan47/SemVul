gt_initstorematch(Storematchinfo *storematch,
                    const GtEncseq *encseq)
{
  unsigned long numofdbsequences = gt_encseq_num_of_sequences(encseq);

  storematch->encseq = encseq;
  GT_INITBITTAB(storematch->hasmatch,numofdbsequences);
}
