s48_make_string_2(s48_call_t call, int length, long init)
{
  int i;
  s48_ref_t ref = s48_make_local_ref(call, s48_allocate_string(length));

  for (i = 0; i < length; ++i)
    s48_string_set(s48_deref(ref), i, init);
  return ref;
}
