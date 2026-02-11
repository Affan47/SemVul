note_reg_clobber (int r)
{
  if (sched_deps_info->note_reg_clobber)
    sched_deps_info->note_reg_clobber (r);
}
