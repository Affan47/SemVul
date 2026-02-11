gt_csa_splice_form_genomic_range(const GtCSASpliceForm *splice_form)
{
  GtRange splice_form_range, tmp_range;
  unsigned long i;
  gt_assert(splice_form);
  splice_form_range.start = ~0UL;
  splice_form_range.end = 0UL;
  for (i = 0; i < gt_array_size(splice_form->spliced_alignments); i++) {
    tmp_range = splice_form->get_genomic_range(*(void**)
                                               gt_array_get(splice_form
                                                         ->spliced_alignments,
                                                         i));
    if (tmp_range.start < splice_form_range.start)
      splice_form_range.start = tmp_range.start;
    if (tmp_range.end > splice_form_range.end)
      splice_form_range.end = tmp_range.end;
  }
  return splice_form_range;
}
