aarch64_select_cc_mode (RTX_CODE code, rtx x, rtx y)
{


  if (GET_MODE_CLASS (GET_MODE (x)) == MODE_FLOAT)
    {
      switch (code)
	{
	case EQ:
	case NE:
	case UNORDERED:
	case ORDERED:
	case UNLT:
	case UNLE:
	case UNGT:
	case UNGE:
	case UNEQ:
	case LTGT:
	  return CCFPmode;

	case LT:
	case LE:
	case GT:
	case GE:
	  return CCFPEmode;

	default:
	  gcc_unreachable ();
	}
    }

  if ((GET_MODE (x) == SImode || GET_MODE (x) == DImode)
      && y == const0_rtx
      && (code == EQ || code == NE || code == LT || code == GE)
      && (GET_CODE (x) == PLUS || GET_CODE (x) == MINUS || GET_CODE (x) == AND
	  || GET_CODE (x) == NEG))
    return CC_NZmode;


  if ((GET_MODE (x) == SImode || GET_MODE (x) == DImode)
      && (GET_CODE (y) == REG || GET_CODE (y) == SUBREG)
      && (GET_CODE (x) == ASHIFT || GET_CODE (x) == ASHIFTRT
	  || GET_CODE (x) == LSHIFTRT
	  || GET_CODE (x) == ZERO_EXTEND || GET_CODE (x) == SIGN_EXTEND))
    return CC_SWPmode;


  if ((GET_MODE (x) == SImode || GET_MODE (x) == DImode)
      && (GET_CODE (y) == REG || GET_CODE (y) == SUBREG)
      && (code == EQ || code == NE)
      && GET_CODE (x) == NEG)
    return CC_Zmode;


  if ((GET_MODE (x) == QImode || GET_MODE (x) == HImode)
      && y == const0_rtx)

    return ((code == GT || code == GE || code == LE || code == LT)
	    ? CC_SESWPmode : CC_ZESWPmode);


  return CCmode;
}
