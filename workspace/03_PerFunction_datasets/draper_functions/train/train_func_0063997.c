lj_ctype_getname(CTState *cts, CType **ctp, GCstr *name, uint32_t tmask)
{
  CTypeID id = cts->hash[ct_hashname(name)];
  while (id) {
    CType *ct = ctype_get(cts, id);
    if (gcref(ct->name) == obj2gco(name) &&
	((tmask >> ctype_type(ct->info)) & 1)) {
      *ctp = ct;
      return id;
    }
    id = ct->next;
  }
  *ctp = &cts->tab[0];
  return 0;
}
