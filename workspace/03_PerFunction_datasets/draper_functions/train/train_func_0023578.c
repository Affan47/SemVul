insn_templ_operand_count (const insn_templ *t)
{
  int i = 0;
  const opname_map_e *op;

  for (op = t->operand_map.head; op != NULL; op = op->next, i++)
    ;
  return i;
}
