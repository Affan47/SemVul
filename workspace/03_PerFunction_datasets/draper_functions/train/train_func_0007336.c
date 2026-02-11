mark(const Identifier *ident, unsigned flags)
{
  BoundVar *bv = find(ident);
  if (bv && !bv->reboundCount)
    bv->flags |= flags;
}
