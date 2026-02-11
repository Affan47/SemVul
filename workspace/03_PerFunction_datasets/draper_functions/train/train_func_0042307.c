gdb_maybe_valid_type_p (SCM value)
{
  return SCM_IMP (value) || scm_in_heap_p (value);
}
