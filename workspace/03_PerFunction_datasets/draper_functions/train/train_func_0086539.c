print_pseudo_live_ranges (FILE *f, int regno)
{
  if (lra_reg_info[regno].live_ranges == NULL)
    return;
  fprintf (f, " r%d:", regno);
  lra_print_live_range_list (f, lra_reg_info[regno].live_ranges);
}
