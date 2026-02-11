final_forward_branch_p (insn)
     rtx insn;
{
  int insn_id, label_id;
  if (!uid_shuid)
    abort ();
  insn_id = INSN_SHUID (insn);
  label_id = INSN_SHUID (JUMP_LABEL (insn));

  if (!insn_id || !label_id)
    abort ();
  return insn_id < label_id;
}
