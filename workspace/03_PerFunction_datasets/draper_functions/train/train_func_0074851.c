in_fallthru_bb_p (rtx insn, rtx succ)
{
  basic_block bb = BLOCK_FOR_INSN (insn);
  edge e;

  if (bb == BLOCK_FOR_INSN (succ))
    return true;

  e = find_fallthru_edge_from (bb);
  if (e)
    bb = e->dest;
  else
    return false;

  while (sel_bb_empty_p (bb))
    bb = bb->next_bb;

  return bb == BLOCK_FOR_INSN (succ);
}
