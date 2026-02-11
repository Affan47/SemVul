lj_ccall_func(lua_State *L, GCcdata *cd)
{
  CTState *cts = ctype_cts(L);
  CType *ct = ctype_raw(cts, cd->ctypeid);
  CTSize sz = CTSIZE_PTR;
  if (ctype_isptr(ct->info)) {
    sz = ct->size;
    ct = ctype_rawchild(cts, ct);
  }
  if (ctype_isfunc(ct->info)) {
    CCallState cc;
    int gcsteps, ret;
    cc.func = (void (*)(void))cdata_getptr(cdataptr(cd), sz);
    gcsteps = ccall_set_args(L, cts, ct, &cc);
    ct = (CType *)((intptr_t)ct-(intptr_t)cts->tab);
    cts->cb.slot = ~0u;
    lj_vm_ffi_call(&cc);
    if (cts->cb.slot != ~0u) {
      TValue tv;
      setlightudV(&tv, (void *)cc.func);
      setboolV(lj_tab_set(L, cts->miscmap, &tv), 1);
    }
    ct = (CType *)((intptr_t)ct+(intptr_t)cts->tab);
    gcsteps += ccall_get_results(L, cts, ct, &cc, &ret);
#if LJ_TARGET_X86 && LJ_ABI_WIN

    if (cc.spadj && ctype_cconv(ct->info) == CTCC_CDECL) {
      CTF_INSERT(ct->info, CCONV, CTCC_STDCALL);
      lj_trace_abort(G(L));
    }
#endif
    while (gcsteps-- > 0)
      lj_gc_check(L);
    return ret;
  }
  return -1;
}
