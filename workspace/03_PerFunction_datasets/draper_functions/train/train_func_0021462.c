xg_resolve_literals (TInsn *insn, symbolS *lit_sym)
{
  symbolS *sym = get_special_literal_symbol ();
  int i;
  if (lit_sym == 0)
    return;
  gas_assert (insn->insn_type == ITYPE_INSN);
  for (i = 0; i < insn->ntok; i++)
    if (insn->tok[i].X_add_symbol == sym)
      insn->tok[i].X_add_symbol = lit_sym;

}
