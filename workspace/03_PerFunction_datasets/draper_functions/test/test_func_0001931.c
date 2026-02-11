fix_bb_live_info (bitmap live, bitmap removed_pseudos)
{
  unsigned int regno;
  bitmap_iterator bi;

  EXECUTE_IF_SET_IN_BITMAP (removed_pseudos, 0, regno, bi)
    if (bitmap_clear_bit (live, regno))
      bitmap_set_bit (live, lra_reg_info[regno].restore_regno);
}
