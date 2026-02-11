note_constraint (rtx exp, int lineno)
{
  const char *name = XSTR (exp, 0);
  unsigned int namelen = strlen (name);
  struct constraint_data **iter, **slot, *new_cdata;


  if (strchr (indep_constraints, name[0]) && name[0] != 'm')
    {
      if (name[1] == '\0')
	message_with_line (lineno, "constraint letter '%s' cannot be "
			   "redefined by the machine description", name);
      else
	message_with_line (lineno, "constraint name '%s' cannot be defined by "
			   "the machine description, as it begins with '%c'",
			   name, name[0]);
      have_error = 1;
      return;
    }

  slot = &constraints_by_letter_table[(unsigned int)name[0]];
  for (iter = slot; *iter; iter = &(*iter)->next_this_letter)
    {


      if ((*iter)->namelen >= namelen)
	slot = iter;

      if (!strcmp ((*iter)->name, name))
	{
	  message_with_line (lineno, "redefinition of constraint '%s'", name);
	  message_with_line ((*iter)->lineno, "previous definition is here");
	  have_error = 1;
	  return;
	}
      else if (!strncmp ((*iter)->name, name, (*iter)->namelen))
	{
	  message_with_line (lineno, "defining constraint '%s' here", name);
	  message_with_line ((*iter)->lineno, "renders constraint '%s' "
			     "(defined here) a prefix", (*iter)->name);
	  have_error = 1;
	  return;
	}
      else if (!strncmp ((*iter)->name, name, namelen))
	{
	  message_with_line (lineno, "constraint '%s' is a prefix", name);
	  message_with_line ((*iter)->lineno, "of constraint '%s' "
			     "(defined here)", (*iter)->name);
	  have_error = 1;
	  return;
	}
    }
  new_cdata = XNEWVAR (struct constraint_data, sizeof (struct constraint_data) + namelen);
  strcpy ((char *)new_cdata + offsetof(struct constraint_data, name), name);
  new_cdata->namelen = namelen;
  new_cdata->lineno = lineno;
  new_cdata->next_this_letter = *slot;
  *slot = new_cdata;
}
