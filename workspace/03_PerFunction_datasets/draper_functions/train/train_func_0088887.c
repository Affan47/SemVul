s48_pop_to (s48_call_t call)
{
  while (current_call != call) {
    s48_call_t here = current_call;
    if (!here)
      s48_assertion_violation ("s48_pop_to", "current_call is null", 0);
    current_call = here->older_call;
    free_call (here);
#ifdef DEBUG_FFI
    fprintf (stderr, "pop\n");
#endif
  }
}
