read_state_gc_used (enum gc_used_enum *pgus)
{
  struct state_token_st *t0 = peek_state_token (0);
  if (state_token_is_name (t0, "gc_unused"))
    *pgus = GC_UNUSED;
  else if (state_token_is_name (t0, "gc_used"))
    *pgus = GC_USED;
  else if (state_token_is_name (t0, "gc_maybe_pointed_to"))
    *pgus = GC_MAYBE_POINTED_TO;
  else if (state_token_is_name (t0, "gc_pointed_to"))
    *pgus = GC_POINTED_TO;
  else
    fatal_reading_state (t0, "invalid gc_used information");
  next_state_tokens (1);
}
