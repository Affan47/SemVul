canon_list_insert (rtx dest ATTRIBUTE_UNUSED, const_rtx unused1 ATTRIBUTE_UNUSED,
		   void * v_insn)
{
  rtx dest_addr, insn;
  int bb;

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

  canon_modify_mem_list[bb] =
    alloc_EXPR_LIST (VOIDmode, dest_addr, canon_modify_mem_list[bb]);
  canon_modify_mem_list[bb] =
    alloc_EXPR_LIST (VOIDmode, dest, canon_modify_mem_list[bb]);
}
