model_index (rtx insn)
{
  if (INSN_MODEL_INDEX (insn) == 0)
    return model_num_insns;
  return INSN_MODEL_INDEX (insn) - 1;
}
