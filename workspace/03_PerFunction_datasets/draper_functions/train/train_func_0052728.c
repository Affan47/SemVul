lra_push_insn_1 (rtx insn, bool always_update)
{
  unsigned int uid = INSN_UID (insn);
  if (always_update)
    lra_update_insn_regno_info (insn);
  if (uid >= SBITMAP_SIZE (lra_constraint_insn_stack_bitmap))
    lra_constraint_insn_stack_bitmap =
      sbitmap_resize (lra_constraint_insn_stack_bitmap, 3 * uid / 2, 0);
  if (bitmap_bit_p (lra_constraint_insn_stack_bitmap, uid))
    return;
  bitmap_set_bit (lra_constraint_insn_stack_bitmap, uid);
  if (! always_update)
    lra_update_insn_regno_info (insn);
  lra_constraint_insn_stack.safe_push (insn);
}
