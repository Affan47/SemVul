print_gen_entry_insns (gen_entry *table,
		       error_func *print,
		       char *first_message, char *next_message)
{
  insn_list *i;
  char *message;
  message = first_message;
  for (i = table->insns; i != NULL; i = i->next)
    {
      insn_entry *insn = i->insn;
      print_gen_entry_path (insn->line, table, print);
      print (NULL, ": %s.%s %s\n", insn->format_name, insn->name, message);
      if (next_message != NULL)
	message = next_message;
    }
}
