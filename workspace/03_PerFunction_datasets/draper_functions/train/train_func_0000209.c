m68hc11_notice_update_cc (exp, insn)
     rtx exp;
     rtx insn ATTRIBUTE_UNUSED;
{

  if (GET_CODE (exp) == SET)
    {

      if (SET_DEST (exp) == pc_rtx)
	;


      else if (GET_CODE (SET_SRC (exp)) == CALL)
	{
	  CC_STATUS_INIT;
	}


      else if (SET_DEST (exp) == cc0_rtx)
	{
	  cc_status.flags = 0;
	  cc_status.value1 = XEXP (exp, 0);
	  cc_status.value2 = XEXP (exp, 1);
	}
      else
	{

	  cc_status.flags = 0;
	  cc_status.value1 = XEXP (exp, 0);
	  cc_status.value2 = XEXP (exp, 1);
	}
    }
  else
    {


      CC_STATUS_INIT;
    }

  if (cc_status.value2 != 0)
    switch (GET_CODE (cc_status.value2))
      {


      case IOR:
      case XOR:
      case AND:
	break;


      case NOT:
	if (GET_MODE (cc_status.value2) != QImode)
	  CC_STATUS_INIT;
	break;

      case PLUS:
      case MINUS:
      case MULT:
      case DIV:
      case UDIV:
      case MOD:
      case UMOD:
      case NEG:
	if (GET_MODE (cc_status.value2) != VOIDmode)
	  cc_status.flags |= CC_NO_OVERFLOW;
	break;


      case ASHIFT:
      case ROTATE:
      case ROTATERT:
	if (GET_MODE (cc_status.value2) != VOIDmode)
	  cc_status.flags |= CC_NO_OVERFLOW;
	break;


      case MEM:
      case SYMBOL_REF:
      case REG:
      case CONST_INT:
	cc_status.flags |= CC_NO_OVERFLOW;
	break;

      default:
	break;
      }
  if (cc_status.value1 && GET_CODE (cc_status.value1) == REG
      && cc_status.value2
      && reg_overlap_mentioned_p (cc_status.value1, cc_status.value2))
    cc_status.value2 = 0;

  else if (cc_status.value1 && side_effects_p (cc_status.value1))
    cc_status.value1 = 0;

  else if (cc_status.value2 && side_effects_p (cc_status.value2))
    cc_status.value2 = 0;
}
