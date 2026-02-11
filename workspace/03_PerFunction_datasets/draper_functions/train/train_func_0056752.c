notice_stack_pointer_modification (void)
{
  basic_block bb;
  rtx insn;


  crtl->sp_is_unchanging = !cfun->calls_alloca;
  if (crtl->sp_is_unchanging)
    FOR_EACH_BB (bb)
      FOR_BB_INSNS (bb, insn)
        {
	  if (INSN_P (insn))
	    {

	      note_stores (PATTERN (insn),
			   notice_stack_pointer_modification_1,
			   NULL);
	      if (! crtl->sp_is_unchanging)
		return;
	    }
	}


  if (df && crtl->sp_is_unchanging)
    df_update_exit_block_uses ();
}
