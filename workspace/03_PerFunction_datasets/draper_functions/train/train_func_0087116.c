gt_seq_iterator_sequence_buffer_set_symbolmap(GtSeqIterator *si,
                                                         const GtUchar
                                                           *symbolmap)
{
  GtSeqIteratorSequenceBuffer *seqit;
  gt_assert(si);
  seqit = gt_seq_iterator_sequence_buffer_cast(si);
  gt_sequence_buffer_set_symbolmap(seqit->fb, symbolmap);
}
