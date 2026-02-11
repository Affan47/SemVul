print_goto_switch_name (lf *file, gen_entry *entry)
{
  lf_printf (file, "case_");
  if (entry->opcode == NULL)
    {
      print_function_name (file,
			   entry->insns->insn->name,
			   entry->insns->insn->format_name,
			   NULL,
			   entry->expanded_bits,
			   (options.gen.icache
			    ? function_name_prefix_icache
			    : function_name_prefix_semantics));
    }
  else
    {
      lf_print_table_name (file, entry);
    }
}
