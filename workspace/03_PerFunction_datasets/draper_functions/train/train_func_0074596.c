dep_spec_p (dep_t dep)
{
  if (current_sched_info->flags & DO_SPECULATION)
    {
      if (DEP_STATUS (dep) & SPECULATIVE)
	return true;
    }
  if (current_sched_info->flags & DO_PREDICATION)
    {
      if (DEP_TYPE (dep) == REG_DEP_CONTROL)
	return true;
    }
  return false;
}
