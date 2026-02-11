insn_finishes_cycle_p (rtx insn)
{
  if (SCHED_GROUP_P (insn))


    return true;


  if (current_sched_info->insn_finishes_block_p
      && current_sched_info->insn_finishes_block_p (insn))
    return true;

  return false;
}
