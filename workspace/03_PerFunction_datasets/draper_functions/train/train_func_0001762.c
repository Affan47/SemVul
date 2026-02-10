update_bitmap_cache (expr_t expr, insn_t insn, bool inside_insn_group,
                     enum MOVEUP_EXPR_CODE res)
{
  int expr_uid = INSN_UID (EXPR_INSN_RTX (expr));


  if (inside_insn_group)
    return;

  if (res == MOVEUP_EXPR_NULL)
    {
      bitmap_set_bit (INSN_ANALYZED_DEPS (insn), expr_uid);
      bitmap_set_bit (INSN_FOUND_DEPS (insn), expr_uid);
    }
  else if (res == MOVEUP_EXPR_SAME)
    {
      bitmap_set_bit (INSN_ANALYZED_DEPS (insn), expr_uid);
      bitmap_clear_bit (INSN_FOUND_DEPS (insn), expr_uid);
    }
  else if (res == MOVEUP_EXPR_AS_RHS)
    {
      bitmap_clear_bit (INSN_ANALYZED_DEPS (insn), expr_uid);
      bitmap_set_bit (INSN_FOUND_DEPS (insn), expr_uid);
    }
  else
    gcc_unreachable ();
}
