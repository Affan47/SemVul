write_attr_value (FILE *outf, struct attr_desc *attr, rtx value)
{
  int op;

  switch (GET_CODE (value))
    {
    case CONST_STRING:
      write_attr_valueq (outf, attr, XSTR (value, 0));
      break;

    case CONST_INT:
      fprintf (outf, HOST_WIDE_INT_PRINT_DEC, INTVAL (value));
      break;

    case SYMBOL_REF:
      fprint_c_condition (outf, XSTR (value, 0));
      break;

    case ATTR:
      {
	struct attr_desc *attr2 = find_attr (&XSTR (value, 0), 0);
	if (attr->enum_name)
	  fprintf (outf, "(enum %s)", attr->enum_name);
	else if (!attr->is_numeric)
	  fprintf (outf, "(enum attr_%s)", attr->name);
	else if (!attr2->is_numeric)
	  fprintf (outf, "(int)");

	fprintf (outf, "get_attr_%s (%s)", attr2->name,
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
      write_attr_value (outf, attr, XEXP (value, 0));
      fputc (' ', outf);
      fputc (op,  outf);
      fputc (' ', outf);
      write_attr_value (outf, attr, XEXP (value, 1));
      break;

    default:
      gcc_unreachable ();
    }
}
