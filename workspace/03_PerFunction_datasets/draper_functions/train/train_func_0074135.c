free_call (s48_call_t call)
{
  if (call->child) {
    s48_call_t c = call->child;

    do {
      s48_call_t temp = c;
      c = c->next_subcall;
      free_call (temp);
    } while (c != call->child);
  }
  free_bv_group (call, call->local_bvs);
  free_ref_group (call->local_refs);
  free_buf_group (call->local_bufs);
#ifdef DEBUG_FFI
  fprintf (stderr, "free_call\n");
  fprintf(stderr, "  count calls: %d, localrefs: %d, globalrefs: %d\n",
	  count_calls(), count_local_refs (), count_global_refs());
#endif
  free (call);
}
