next_insn_in_loop (const struct loop *loop, rtx insn)
{
  insn = NEXT_INSN (insn);

  if (insn == loop->end)
    {
      if (loop->top)

	insn = loop->top;
      else

	insn = NULL_RTX;
    }

  if (insn == loop->scan_start)

    insn = NULL_RTX;

  return insn;
}
