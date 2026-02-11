unshare_all_rtl_again (rtx insn)
{
  rtx p;
  tree decl;

  for (p = insn; p; p = NEXT_INSN (p))
    if (INSN_P (p))
      {
	reset_used_flags (PATTERN (p));
	reset_used_flags (REG_NOTES (p));
	if (CALL_P (p))
	  reset_used_flags (CALL_INSN_FUNCTION_USAGE (p));
      }


  set_used_decls (DECL_INITIAL (cfun->decl));


  for (decl = DECL_ARGUMENTS (cfun->decl); decl; decl = DECL_CHAIN (decl))
    set_used_flags (DECL_RTL (decl));

  reset_used_flags (stack_slot_list);

  unshare_all_rtl_1 (insn);
}
