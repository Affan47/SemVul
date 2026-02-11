gth_ags_left_intron_border(const GthAGS *ags,
                                            unsigned long intron)
{
  GthExonAGS *exon;
  gt_assert(ags);
  exon = gth_ags_get_exon(ags, intron);
  return SHOWGENPOSAGS(exon->range.end + 1);
}
