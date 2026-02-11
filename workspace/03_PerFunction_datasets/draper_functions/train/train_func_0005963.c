tinsn_has_symbolic_operands (const TInsn *insn)
{
  int i;
  int n = insn->ntok;

  gas_assert (insn->insn_type == ITYPE_INSN);

  for (i = 0; i < n; ++i)
    {
      switch (insn->tok[i].X_op)
	{
	case O_register:
	case O_constant:
	  break;
	default:
	  return TRUE;
	}
    }
  return FALSE;
}
