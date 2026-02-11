s48_free_local_ref (s48_call_t call, s48_ref_t ref)
{
#ifdef DEBUG_FFI
  fprintf (stderr, "free local ref with scheme value %x\n", s48_deref(ref));
#endif
  if (!GLOBAL_REF_P (ref))
    free_ref (ref);
  else
    s48_assertion_violation ("s48_free_localref", "ref is not local", 0);
}
