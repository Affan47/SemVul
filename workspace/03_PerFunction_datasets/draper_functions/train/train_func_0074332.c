gt_samfile_encseq_mapping_seqnum(
    GtSamfileEncseqMapping *samfile_encseq_mapping,
    int32_t reference_num)
{
  gt_assert(samfile_encseq_mapping != NULL);
  gt_assert(reference_num < (int32_t)samfile_encseq_mapping->nof_sequences);
  return samfile_encseq_mapping->samfile2encseq[reference_num];
}
