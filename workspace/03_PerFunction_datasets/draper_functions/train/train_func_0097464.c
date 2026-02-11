zx_el_desc_lookup(int tok)
{
  struct zx_el_desc* ed;
  if (tok == ZX_TOK_NOT_FOUND)
    return 0;
  if (!IN_RANGE(tok & ZX_TOK_TOK_MASK, 0, zx__ELEM_MAX)) {
    ERR("out of range token 0x%06x", tok);
    return 0;
  }
  for (ed = zx_el_tab[tok & ZX_TOK_TOK_MASK].n; ed; ed = ed->n)
    if (ed->tok == tok)
      return ed;
  ERR("unknown token 0x%06x", tok);
  return 0;
}
