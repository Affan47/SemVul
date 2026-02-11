gt_assembly_stats_calculator_add(GtAssemblyStatsCalculator *asc,
    unsigned long length)
{
  gt_assert(asc != NULL);
  gt_assert(length != 0);
  gt_disc_distri_add(asc->lengths, length);
  (asc->numofseq)++;
  asc->sumlength += length;
  if (asc->minlength == 0 || length < asc->minlength)
    asc->minlength = length;
  if (length > asc->maxlength)
    asc->maxlength = length;
}
