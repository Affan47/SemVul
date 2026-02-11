a_teardown(pTHX_ void *root) {

 if (!a_initialized)
  return;

#if A_MULTIPLICITY
 if (aTHX != root)
  return;
#endif

 {
  dMY_CXT;
# if A_THREADSAFE && A_WORKAROUND_REQUIRE_PROPAGATION
  ptable_hints_free(MY_CXT.tbl);
# endif
  ptable_seen_free(MY_CXT.seen);
 }

 a_ck_restore(OP_PADANY, &a_old_ck_padany);
 a_ck_restore(OP_PADSV,  &a_old_ck_padsv);

 a_ck_restore(OP_AELEM,  &a_old_ck_aelem);
 a_ck_restore(OP_HELEM,  &a_old_ck_helem);
 a_ck_restore(OP_RV2SV,  &a_old_ck_rv2sv);

 a_ck_restore(OP_RV2AV,  &a_old_ck_rv2av);
 a_ck_restore(OP_RV2HV,  &a_old_ck_rv2hv);

 a_ck_restore(OP_ASLICE, &a_old_ck_aslice);
 a_ck_restore(OP_HSLICE, &a_old_ck_hslice);

 a_ck_restore(OP_EXISTS, &a_old_ck_exists);
 a_ck_restore(OP_DELETE, &a_old_ck_delete);
 a_ck_restore(OP_KEYS,   &a_old_ck_keys);
 a_ck_restore(OP_VALUES, &a_old_ck_values);

#if A_HAS_RPEEP
 PL_rpeepp  = a_old_peep;
#else
 PL_peepp   = a_old_peep;
#endif
 a_old_peep = 0;

 a_initialized = 0;
}
