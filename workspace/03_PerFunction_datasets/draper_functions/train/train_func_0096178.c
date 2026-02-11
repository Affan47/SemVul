asm_source_entry_parse_operand (AsmSourceEntry * entry, gint * value)
{
  g_assert (entry);
  return asm_source_entry_parse_not_operand_but_this (entry, value,
													  entry->s_opnd);
}
