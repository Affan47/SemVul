write_attr_case (struct attr_desc *attr, struct attr_value *av,
		 int write_case_lines, const char *prefix, const char *suffix,
		 int indent, rtx known_true)
{
  struct insn_ent *ie;

  if (av->num_insns == 0)
    return;

  if (av->has_asm_insn)
    {
      write_indent (indent);
      printf ("case -1:\n");
      write_indent (indent + 2);
      printf ("if (GET_CODE (PATTERN (insn)) != ASM_INPUT\n");
      write_indent (indent + 2);
      printf ("    && asm_noperands (PATTERN (insn)) < 0)\n");
      write_indent (indent + 2);
      printf ("  fatal_insn_not_found (insn);\n");
    }

  if (write_case_lines)
    {
      for (ie = av->first_insn; ie; ie = ie->next)
	if (ie->insn_code != -1)
	  {
	    write_indent (indent);
	    printf ("case %d:\n", ie->insn_code);
	  }
    }
  else
    {
      write_indent (indent);
      printf ("default:\n");
    }


  must_extract = must_constrain = address_used = 0;
  walk_attr_value (av->value);

  if (must_constrain)
    {
      write_indent (indent + 2);
      printf ("extract_constrain_insn_cached (insn);\n");
    }
  else if (must_extract)
    {
      write_indent (indent + 2);
      printf ("extract_insn_cached (insn);\n");
    }

  write_attr_set (attr, indent + 2, av->value, prefix, suffix,
		  known_true, av->first_insn->insn_code,
		  av->first_insn->insn_index);

  if (strncmp (prefix, "return", 6))
    {
      write_indent (indent + 2);
      printf ("break;\n");
    }
  printf ("\n");
}
