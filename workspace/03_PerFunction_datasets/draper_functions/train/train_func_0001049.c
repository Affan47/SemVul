get_exons(GtArray *exon_ranges, const void *sa)
{
  GtSSplicedAlignment *alignment = *(GtSSplicedAlignment**) sa;
  GtRange exon;
  unsigned long i;
  gt_assert(alignment);
  for (i = 0; i < gt_sspliced_alignment_num_of_exons(alignment); i++) {
    exon = gt_sspliced_alignment_get_exon(alignment, i);
    gt_array_add(exon_ranges, exon);
  }
}
