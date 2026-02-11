print_case_clauses (clauses)
     PATTERN_LIST *clauses;
{
  indentation += indentation_amount;
  while (clauses)
    {
      newline ("");
      command_print_word_list (clauses->patterns, " | ");
      cprintf (")\n");
      indentation += indentation_amount;
      make_command_string_internal (clauses->action);
      indentation -= indentation_amount;
      if (clauses->flags & CASEPAT_FALLTHROUGH)
	newline (";&");
      else if (clauses->flags & CASEPAT_TESTNEXT)
	newline (";;&");
      else
	newline (";;");
      clauses = clauses->next;
    }
  indentation -= indentation_amount;
}
