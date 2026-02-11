miniexp_to_name(miniexp_t p)
{
  if (miniexp_symbolp(p))
    {
      struct symtable_t::sym *r;
      r = ((symtable_t::sym*)(((size_t)p)&~((size_t)3)));
      return r->n;
    }
  return 0;
}
