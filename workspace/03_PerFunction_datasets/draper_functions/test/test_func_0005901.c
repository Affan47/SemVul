s_mri_common (int small ATTRIBUTE_UNUSED)
{
  char *name;
  char c;
  char *alc = NULL;
  symbolS *sym;
  offsetT align;
  char *stop = NULL;
  char stopc = 0;

  if (!flag_mri)
    {
      s_comm (0);
      return;
    }

  stop = mri_comment_field (&stopc);

  SKIP_WHITESPACE ();

  name = input_line_pointer;
  if (!ISDIGIT (*name))
    c = get_symbol_end ();
  else
    {
      do
	{
	  ++input_line_pointer;
	}
      while (ISDIGIT (*input_line_pointer));

      c = *input_line_pointer;
      *input_line_pointer = '\0';

      if (line_label != NULL)
	{
	  alc = (char *) xmalloc (strlen (S_GET_NAME (line_label))
				  + (input_line_pointer - name)
				  + 1);
	  sprintf (alc, "%s%s", name, S_GET_NAME (line_label));
	  name = alc;
	}
    }

  sym = symbol_find_or_make (name);
  *input_line_pointer = c;
  if (alc != NULL)
    free (alc);

  if (*input_line_pointer != ',')
    align = 0;
  else
    {
      ++input_line_pointer;
      align = get_absolute_expression ();
    }

  if (S_IS_DEFINED (sym) && !S_IS_COMMON (sym))
    {
      as_bad (_("symbol `%s' is already defined"), S_GET_NAME (sym));
      ignore_rest_of_line ();
      mri_comment_end (stop, stopc);
      return;
    }

  S_SET_EXTERNAL (sym);
  S_SET_SEGMENT (sym, bfd_com_section_ptr);
  mri_common_symbol = sym;

#ifdef S_SET_ALIGN
  if (align != 0)
    S_SET_ALIGN (sym, align);
#else
  (void) align;
#endif

  if (line_label != NULL)
    {
      expressionS exp;
      exp.X_op = O_symbol;
      exp.X_add_symbol = sym;
      exp.X_add_number = 0;
      symbol_set_value_expression (line_label, &exp);
      symbol_set_frag (line_label, &zero_address_frag);
      S_SET_SEGMENT (line_label, expr_section);
    }


  if (*input_line_pointer == ',')
    input_line_pointer += 2;
  if (*input_line_pointer == ',')
    input_line_pointer += 2;

  demand_empty_rest_of_line ();

  mri_comment_end (stop, stopc);
}
