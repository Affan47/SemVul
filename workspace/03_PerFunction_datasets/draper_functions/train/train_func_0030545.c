initiate_reg_pressure_info (bitmap live)
{
  int i;
  unsigned int j;
  bitmap_iterator bi;

  for (i = 0; i < ira_reg_class_cover_size; i++)
    curr_reg_pressure[ira_reg_class_cover[i]] = 0;
  bitmap_clear (curr_reg_live);
  EXECUTE_IF_SET_IN_BITMAP (live, 0, j, bi)
    if (sched_pressure == SCHED_PRESSURE_MODEL
	|| current_nr_blocks == 1
	|| bitmap_bit_p (region_ref_regs, j))
      mark_regno_birth_or_death (curr_reg_live, curr_reg_pressure, j, true);
}
