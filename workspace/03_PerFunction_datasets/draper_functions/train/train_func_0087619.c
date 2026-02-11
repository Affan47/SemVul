merge_outer_ops (enum rtx_code *pop0, HOST_WIDE_INT *pconst0, enum rtx_code op1, HOST_WIDE_INT const1, enum machine_mode mode, int *pcomp_p)
{
  enum rtx_code op0 = *pop0;
  HOST_WIDE_INT const0 = *pconst0;

  const0 &= GET_MODE_MASK (mode);
  const1 &= GET_MODE_MASK (mode);


  if (op0 == AND)
    const1 &= const0;


  if (op1 == UNKNOWN || op0 == SET)
    return 1;

  else if (op0 == UNKNOWN)
    op0 = op1, const0 = const1;

  else if (op0 == op1)
    {
      switch (op0)
	{
	case AND:
	  const0 &= const1;
	  break;
	case IOR:
	  const0 |= const1;
	  break;
	case XOR:
	  const0 ^= const1;
	  break;
	case PLUS:
	  const0 += const1;
	  break;
	case NEG:
	  op0 = UNKNOWN;
	  break;
	default:
	  break;
	}
    }


  else if (op0 == PLUS || op1 == PLUS || op0 == NEG || op1 == NEG)
    return 0;


  else if (const0 != const1)
    return 0;

  else
    switch (op0)
      {
      case IOR:
	if (op1 == AND)

	  op0 = SET;
	else

	  {;}
	break;

      case XOR:
	if (op1 == AND)

	  op0 = AND, *pcomp_p = 1;
	else

	  op0 = AND, const0 = ~const0;
	break;

      case AND:
	if (op1 == IOR)

	op0 = SET;
	else

	  *pcomp_p = 1;
	break;
      default:
	break;
      }


  const0 &= GET_MODE_MASK (mode);
  if (const0 == 0
      && (op0 == IOR || op0 == XOR || op0 == PLUS))
    op0 = UNKNOWN;
  else if (const0 == 0 && op0 == AND)
    op0 = SET;
  else if ((unsigned HOST_WIDE_INT) const0 == GET_MODE_MASK (mode)
	   && op0 == AND)
    op0 = UNKNOWN;

  *pop0 = op0;


  if (op0 != UNKNOWN && op0 != NEG)
    *pconst0 = trunc_int_for_mode (const0, mode);

  return 1;
}
