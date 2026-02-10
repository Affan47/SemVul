write_attr_value (struct attr_desc *attr, rtx value)
{
  int op;

  switch (GET_CODE (value))
    {
    case CONST_STRING:
      write_attr_valueq (attr, XSTR (value, 0));
      break;

    case CONST_INT:
      printf (HOST_WIDE_INT_PRINT_DEC, INTVAL (value));
      break;

    case SYMBOL_REF:
      fputs (XSTR (value, 0), stdout);
      break;

    case ATTR:
      {
	struct attr_desc *attr2 = find_attr (&XSTR (value, 0), 0);
	printf ("get_attr_%s (%s)", attr2->name,
		(attr2->is_const ? "" : "insn"));
      }
      break;

    case PLUS:
      op = '+';
      goto do_operator;
    case MINUS:
      op = '-';
      goto do_operator;
    case MULT:
      op = '*';
      goto do_operator;
    case DIV:
      op = '/';
      goto do_operator;
    case MOD:
      op = '%';
      goto do_operator;

    do_operator:
      write_attr_value (attr, XEXP (value, 0));
      putchar (' ');
      putchar (op);
      putchar (' ');
      write_attr_value (attr, XEXP (value, 1));
      break;

    default:
      abort ();
    }
}
