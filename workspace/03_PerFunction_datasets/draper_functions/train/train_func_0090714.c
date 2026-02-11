print_operand_address (FILE *file, rtx addr)
{
  switch (GET_CODE (addr))
    {
    case REG:
      fprintf (file, "%s", h8_reg_names[REGNO (addr)]);
      break;

    case PRE_DEC:
      fprintf (file, "-%s", h8_reg_names[REGNO (XEXP (addr, 0))]);
      break;

    case POST_INC:
      fprintf (file, "%s+", h8_reg_names[REGNO (XEXP (addr, 0))]);
      break;

    case PLUS:
      fprintf (file, "(");
      if (GET_CODE (XEXP (addr, 0)) == REG)
	{

	  print_operand_address (file, XEXP (addr, 1));
	  fprintf (file, ",");
	  print_operand_address (file, XEXP (addr, 0));
	}
      else
	{

	  print_operand_address (file, XEXP (addr, 0));
	  fprintf (file, "+");
	  print_operand_address (file, XEXP (addr, 1));
	}
      fprintf (file, ")");
      break;

    case CONST_INT:
      {


	int n = INTVAL (addr);
	if (TARGET_H8300)
	  n = (int) (short) n;
	fprintf (file, "%d", n);
	break;
      }

    default:
      output_addr_const (file, addr);
      break;
    }
}
