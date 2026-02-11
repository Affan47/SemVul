gt_destructSeqReaderSet(SeqReaderSet *readerSet)
{
  gt_assert(readerSet);
  ListDo(struct seqReaderState, readerSet->consumerList, gt_free(p));
  if (readerSet->autoConsumerList)
    gt_free(readerSet->autoConsumerList);
  if (readerSet->seqDataBacklog)
    gt_free(readerSet->seqDataBacklog);
}
