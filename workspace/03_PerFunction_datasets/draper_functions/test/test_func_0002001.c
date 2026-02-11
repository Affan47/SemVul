add_decl_plain (pIIR_DeclarativeRegion region, pIIR_Declaration decl)
{
  decl->declarative_region = region;
  pIIR_DeclarationList dl = mIIR_DeclarationList(decl->pos, decl, NULL);
  if (pIIR_DeclarationList t = tail(region))
    t->rest = dl;
  else
    region->declarations = dl;
  tail(region) = dl;
}
