forwarder_block_p (bb)
     basic_block bb;
{
  rtx insn;

  if (bb == EXIT_BLOCK_PTR || bb == ENTRY_BLOCK_PTR
      || !bb->succ || bb->succ->succ_next)
    return false;

  for (insn = bb->head; insn != bb->end; insn = NEXT_INSN (insn))
    if (INSN_P (insn) && flow_active_insn_p (insn))
      return false;

  return (!INSN_P (insn)
	  || (GET_CODE (insn) == JUMP_INSN && simplejump_p (insn))
	  || !flow_active_insn_p (insn));
}
