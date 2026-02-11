s48_make_vector_2(s48_call_t call, long length, s48_ref_t init)
{
  long i;
  s48_ref_t ref = s48_make_local_ref(call, s48_allocate_stob(S48_STOBTYPE_VECTOR, length));
  for (i = 0; i < length; ++i)
    s48_unsafe_vector_set_2(call, ref, i, init);
  return ref;
}
