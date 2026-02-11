lra_need_for_spills_p (void)
{
  int i; max_regno = max_reg_num ();

  for (i = FIRST_PSEUDO_REGISTER; i < max_regno; i++)
    if (lra_reg_info[i].nrefs != 0 && lra_get_regno_hard_regno (i) < 0
	&& ! lra_former_scratch_p (i))
      return true;
  return false;
}
