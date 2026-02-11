need_nop_to_preserve_insn_bb (rtx insn)
{
  insn_t bb_head, bb_end, bb_next, in_next;
  basic_block bb = BLOCK_FOR_INSN (insn);

  bb_head = sel_bb_head (bb);
  bb_end = sel_bb_end (bb);

  if (bb_head == bb_end)
    return true;

  while (bb_head != bb_end && DEBUG_INSN_P (bb_head))
    bb_head = NEXT_INSN (bb_head);

  if (bb_head == bb_end)
    return true;

  while (bb_head != bb_end && DEBUG_INSN_P (bb_end))
    bb_end = PREV_INSN (bb_end);

  if (bb_head == bb_end)
    return true;

  bb_next = NEXT_INSN (bb_head);
  while (bb_next != bb_end && DEBUG_INSN_P (bb_next))
    bb_next = NEXT_INSN (bb_next);

  if (bb_next == bb_end && JUMP_P (bb_end))
    return true;

  in_next = NEXT_INSN (insn);
  while (DEBUG_INSN_P (in_next))
    in_next = NEXT_INSN (in_next);

  if (IN_CURRENT_FENCE_P (in_next))
    return true;

  return false;
}
