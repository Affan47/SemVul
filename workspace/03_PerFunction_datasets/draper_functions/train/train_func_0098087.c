bcread_kgc(LexState *ls, GCproto *pt, MSize sizekgc)
{
  MSize i;
  GCRef *kr = mref(pt->k, GCRef) - (ptrdiff_t)sizekgc;
  for (i = 0; i < sizekgc; i++, kr++) {
    MSize tp = bcread_uleb128(ls);
    if (tp >= BCDUMP_KGC_STR) {
      MSize len = tp - BCDUMP_KGC_STR;
      const char *p = (const char *)bcread_mem(ls, len);
      setgcref(*kr, obj2gco(lj_str_new(ls->L, p, len)));
    } else if (tp == BCDUMP_KGC_TAB) {
      setgcref(*kr, obj2gco(bcread_ktab(ls)));
#if LJ_HASFFI
    } else if (tp != BCDUMP_KGC_CHILD) {
      CTypeID id = tp == BCDUMP_KGC_COMPLEX ? CTID_COMPLEX_DOUBLE :
		   tp == BCDUMP_KGC_I64 ? CTID_INT64 : CTID_UINT64;
      CTSize sz = tp == BCDUMP_KGC_COMPLEX ? 16 : 8;
      GCcdata *cd = lj_cdata_new_(ls->L, id, sz);
      TValue *p = (TValue *)cdataptr(cd);
      setgcref(*kr, obj2gco(cd));
      p[0].u32.lo = bcread_uleb128(ls);
      p[0].u32.hi = bcread_uleb128(ls);
      if (tp == BCDUMP_KGC_COMPLEX) {
	p[1].u32.lo = bcread_uleb128(ls);
	p[1].u32.hi = bcread_uleb128(ls);
      }
#endif
    } else {
      lua_State *L = ls->L;
      lua_assert(tp == BCDUMP_KGC_CHILD);
      if (L->top <= bcread_oldtop(L, ls))
	bcread_error(ls, LJ_ERR_BCBAD);
      L->top--;
      setgcref(*kr, obj2gco(protoV(L->top)));
    }
  }
}
