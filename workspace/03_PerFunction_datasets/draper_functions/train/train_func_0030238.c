arm_barrier_cost (rtx insn)
{


  int base_cost = 50;
  rtx next = next_nonnote_insn (insn);

  if (next != NULL && GET_CODE (next) == CODE_LABEL)
    base_cost -= 20;

  switch (GET_CODE (insn))
    {
    case CODE_LABEL:


      return 50;

    case INSN:
    case CALL_INSN:
      return base_cost;

    case JUMP_INSN:
      return base_cost - 10;

    default:
      return base_cost + 10;
    }
}
