emit_peobj_sym_sect(BuildCtx *ctx, PEsection *pesect, int sect)
{
  PEsym sym;
  PEsymaux aux;
  if (!strtab) return;
  memcpy(sym.n.name, pesect[sect].name, 8);
  sym.value = 0;
  sym.sect = (int16_t)(sect+1);
  sym.type = PEOBJ_TYPE_NULL;
  sym.scl = PEOBJ_SCL_STATIC;
  sym.naux = 1;
  owrite(ctx, &sym, PEOBJ_SYM_SIZE);
  memset(&aux, 0, sizeof(PEsymaux));
  aux.size = pesect[sect].size;
  aux.nreloc = pesect[sect].nreloc;
  owrite(ctx, &aux, PEOBJ_SYM_SIZE);
}
