gen_attr (rtx exp, int lineno)
{
  struct attr_desc *attr;
  struct attr_value *av;
  const char *name_ptr;
  char *p;


  attr = find_attr (&XSTR (exp, 0), 1);
  if (attr->default_val)
    {
      message_with_line (lineno, "duplicate definition for attribute %s",
			 attr->name);
      message_with_line (attr->lineno, "previous definition");
      have_error = 1;
      return;
    }
  attr->lineno = lineno;

  if (*XSTR (exp, 1) == '\0')
    attr->is_numeric = 1;
  else
    {
      name_ptr = XSTR (exp, 1);
      while ((p = next_comma_elt (&name_ptr)) != NULL)
	{
	  av = oballoc (struct attr_value);
	  av->value = attr_rtx (CONST_STRING, p);
	  av->next = attr->first_value;
	  attr->first_value = av;
	  av->first_insn = NULL;
	  av->num_insns = 0;
	  av->has_asm_insn = 0;
	}
    }

  if (GET_CODE (XEXP (exp, 2)) == CONST)
    {
      attr->is_const = 1;
      if (attr->is_numeric)
	{
	  message_with_line (lineno,
			     "constant attributes may not take numeric values");
	  have_error = 1;
	}


      XEXP (exp, 2) = XEXP (XEXP (exp, 2), 0);
    }

  if (! strcmp_check (attr->name, length_str) && ! attr->is_numeric)
    {
      message_with_line (lineno,
			 "`length' attribute must take numeric values");
      have_error = 1;
    }


  XEXP (exp, 2) = check_attr_value (XEXP (exp, 2), attr);
  attr->default_val = get_attr_value (XEXP (exp, 2), attr, -2);
}
