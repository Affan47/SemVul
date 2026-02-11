compute_max_insns (int insns)
{
  int max_insns = insns;
  if (max_insns < PARAM_VALUE (PARAM_LARGE_UNIT_INSNS))
    max_insns = PARAM_VALUE (PARAM_LARGE_UNIT_INSNS);

  return ((HOST_WIDEST_INT) max_insns
	  * (100 + PARAM_VALUE (PARAM_INLINE_UNIT_GROWTH)) / 100);
}
