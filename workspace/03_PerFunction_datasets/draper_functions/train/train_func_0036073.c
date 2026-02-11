get_next_ref (int regno, basic_block bb, rtx *next_array)
{
  rtx insn = next_array[regno];


  if (insn && BLOCK_FOR_INSN (insn) != bb)
    {
      next_array[regno] = NULL;
      insn = NULL;
    }

  return insn;
}
