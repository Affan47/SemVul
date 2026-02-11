continuation_free (SCM obj)
{
  scm_t_contregs *continuation = SCM_CONTREGS (obj);

  size_t extra_items = (continuation->num_stack_items > 0)
    ? (continuation->num_stack_items - 1)
    : 0;
  size_t bytes_free = sizeof (scm_t_contregs)
    + extra_items * sizeof (SCM_STACKITEM);

#ifdef __ia64__
  scm_gc_free (continuation->backing_store, continuation->backing_store_size,
	       "continuation backing store");
#endif
  scm_gc_free (continuation, bytes_free, "continuation");
  return 0;
}
