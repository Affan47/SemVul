canon_list_insert (rtx dest ATTRIBUTE_UNUSED, const_rtx x ATTRIBUTE_UNUSED,
		   void * v_insn)
{
  rtx dest_addr, insn;
  int bb;
  modify_pair *pair;

  while (GET_CODE (dest) == SUBREG
      || GET_CODE (dest) == ZERO_EXTRACT
      || GET_CODE (dest) == STRICT_LOW_PART)
    dest = XEXP (dest, 0);


  if (! MEM_P (dest))
    return;

  dest_addr = get_addr (XEXP (dest, 0));
  dest_addr = canon_rtx (dest_addr);
  insn = (rtx) v_insn;
  bb = BLOCK_FOR_INSN (insn)->index;

  pair = VEC_safe_push (modify_pair, heap, canon_modify_mem_list[bb], NULL);
  pair->dest = dest;
  pair->dest_addr = dest_addr;
}
