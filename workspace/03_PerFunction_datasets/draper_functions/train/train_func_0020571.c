print_idecode_table (lf *file, gen_entry *entry, const char *result)
{
  lf_printf (file, "/* prime the search */\n");
  lf_printf (file, "idecode_table_entry *table = ");
  lf_print_table_name (file, entry);
  lf_printf (file, ";\n");
  lf_printf (file, "int opcode = EXTRACTED%d (instruction, %d, %d);\n",
	     options.insn_bit_size,
	     i2target (options.hi_bit_nr, entry->opcode->first),
	     i2target (options.hi_bit_nr, entry->opcode->last));
  lf_printf (file, "idecode_table_entry *table_entry = table + opcode;\n");

  lf_printf (file, "\n");
  lf_printf (file, "/* iterate until a leaf */\n");
  lf_printf (file, "while (1) {\n");
  lf_printf (file, "  signed shift = table_entry->shift;\n");
  lf_printf (file, "if (shift == function_entry) break;\n");
  lf_printf (file, "  if (shift >= 0) {\n");
  lf_printf (file, "    table = ((idecode_table_entry*)\n");
  lf_printf (file, "             table_entry->function_or_table);\n");
  lf_printf (file, "    opcode = ((instruction & table_entry->mask)\n");
  lf_printf (file, "              >> shift);\n");
  lf_printf (file, "    table_entry = table + opcode;\n");
  lf_printf (file, "  }\n");
  lf_printf (file, "  else {\n");
  lf_printf (file, "    /* must be a boolean */\n");
  lf_printf (file, "    ASSERT(table_entry->shift == boolean_entry);\n");
  lf_printf (file, "    opcode = ((instruction & table_entry->mask)\n");
  lf_printf (file, "              != table_entry->value);\n");
  lf_printf (file, "    table = ((idecode_table_entry*)\n");
  lf_printf (file, "             table_entry->function_or_table);\n");
  lf_printf (file, "    table_entry = table + opcode;\n");
  lf_printf (file, "  }\n");
  lf_printf (file, "}\n");

  lf_printf (file, "\n");
  lf_printf (file, "/* call the leaf code */\n");
  if (options.gen.code == generate_jumps)
    {
      lf_printf (file, "goto *table_entry->function_or_table;\n");
    }
  else
    {
      lf_printf (file, "%s ", result);
      if (options.gen.icache)
	{
	  lf_printf (file,
		     "(((idecode_icache*)table_entry->function_or_table)\n");
	  lf_printf (file, "  (");
	  print_icache_function_actual (file, 1);
	  lf_printf (file, "));\n");
	}
      else
	{
	  lf_printf (file,
		     "((idecode_semantic*)table_entry->function_or_table)\n");
	  lf_printf (file, "  (");
	  print_semantic_function_actual (file, 1);
	  lf_printf (file, ");\n");
	}
    }
}
