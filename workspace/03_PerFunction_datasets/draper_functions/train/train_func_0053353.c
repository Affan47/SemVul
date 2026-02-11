is_prisky (rtx load_insn, int bb_src, int bb_trg)
{
  if (FED_BY_SPEC_LOAD (load_insn))
    return 1;

  if (sd_lists_empty_p (load_insn, SD_LIST_BACK))

    return 1;

  if (is_conditionally_protected (load_insn, bb_src, bb_trg))
    return 1;

  return 0;
}
