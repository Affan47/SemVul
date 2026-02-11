gt_seq_iterator_sequence_buffer_new_with_buffer(
                                                       GtSequenceBuffer *buffer)
{
  GtSeqIterator *si;
  GtSeqIteratorSequenceBuffer *seqit;
  si = gt_seq_iterator_create(gt_seq_iterator_sequence_buffer_class());
  seqit = gt_seq_iterator_sequence_buffer_cast(si);
  GT_INITARRAY(&seqit->sequencebuffer, GtUchar);
  seqit->descptr = gt_desc_buffer_new();
  seqit->fb = gt_sequence_buffer_ref(buffer);
  gt_sequence_buffer_set_desc_buffer(seqit->fb, seqit->descptr);
  seqit->exhausted = false;
  seqit->unitnum = 0;
  seqit->withsequence = true;
  seqit->currentread = 0;
  seqit->maxread = 0;
  return si;
}
