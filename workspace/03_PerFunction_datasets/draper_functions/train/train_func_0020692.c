gt_samfile_iterator_reference_name(const GtSamfileIterator *s_iter,
                                               int32_t reference_num)
{
  gt_assert(reference_num >= 0);
  gt_assert(reference_num < s_iter->samfile->header->n_targets);
  return s_iter->samfile->header->target_name[reference_num];
}
