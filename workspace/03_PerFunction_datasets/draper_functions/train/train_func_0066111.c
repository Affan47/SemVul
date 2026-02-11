a_setup(pTHX) {
#define a_setup() a_setup(aTHX)
 if (a_initialized)
  return;

 {
  MY_CXT_INIT;
# if A_THREADSAFE && A_WORKAROUND_REQUIRE_PROPAGATION
  MY_CXT.tbl   = ptable_new();
  MY_CXT.owner = aTHX;
# endif
  MY_CXT.seen  = ptable_new();
 }

 a_ck_replace(OP_PADANY, a_ck_padany, &a_old_ck_padany);
 a_ck_replace(OP_PADSV,  a_ck_padsv,  &a_old_ck_padsv);

 a_ck_replace(OP_AELEM,  a_ck_deref,  &a_old_ck_aelem);
 a_ck_replace(OP_HELEM,  a_ck_deref,  &a_old_ck_helem);
 a_ck_replace(OP_RV2SV,  a_ck_deref,  &a_old_ck_rv2sv);

 a_ck_replace(OP_RV2AV,  a_ck_rv2xv,  &a_old_ck_rv2av);
 a_ck_replace(OP_RV2HV,  a_ck_rv2xv,  &a_old_ck_rv2hv);

 a_ck_replace(OP_ASLICE, a_ck_xslice, &a_old_ck_aslice);
 a_ck_replace(OP_HSLICE, a_ck_xslice, &a_old_ck_hslice);

 a_ck_replace(OP_EXISTS, a_ck_root,   &a_old_ck_exists);
 a_ck_replace(OP_DELETE, a_ck_root,   &a_old_ck_delete);
 a_ck_replace(OP_KEYS,   a_ck_root,   &a_old_ck_keys);
 a_ck_replace(OP_VALUES, a_ck_root,   &a_old_ck_values);

#if A_HAS_RPEEP
 a_old_peep = PL_rpeepp;
 PL_rpeepp  = a_peep;
#else
 a_old_peep = PL_peepp;
 PL_peepp   = a_peep;
#endif

#if A_MULTIPLICITY
 call_atexit(a_teardown, aTHX);
#else
 call_atexit(a_teardown, NULL);
#endif

 a_initialized = 1;
}
