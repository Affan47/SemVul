perhaps_ends_bb_p (insn)
     rtx insn;
{
  switch (GET_CODE (insn))
    {
    case CODE_LABEL:
    case JUMP_INSN:

      return 1;

    case CALL_INSN:


      if (nonlocal_goto_handler_labels)
	return 1;

    default:
      return can_throw_internal (insn);
    }
}
