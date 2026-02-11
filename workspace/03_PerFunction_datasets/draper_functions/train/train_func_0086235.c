check_function_return_warnings (void)
{
  if (warn_missing_noreturn
      && !TREE_THIS_VOLATILE (cfun->decl)
      && EXIT_BLOCK_PTR->pred == NULL
      && (lang_missing_noreturn_ok_p
	  && !lang_missing_noreturn_ok_p (cfun->decl)))
    warning ("function might be possible candidate for attribute `noreturn'");


  if (TREE_THIS_VOLATILE (cfun->decl)
      && EXIT_BLOCK_PTR->pred != NULL)
    warning ("`noreturn' function does return");


  else if (warn_return_type
	   && cfun->x_clobber_return_insn != NULL
	   && EXIT_BLOCK_PTR->pred != NULL)
    {
      int max_uid = get_max_uid ();


      if (INSN_UID (cfun->x_clobber_return_insn) < max_uid)
	{
	  rtx insn;

	  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
	    if (insn == cfun->x_clobber_return_insn)
	      {
	        warning ("control reaches end of non-void function");
		break;
	      }
	}
    }
}
