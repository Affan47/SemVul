scm_make_continuation (int *first)
{
  scm_i_thread *thread = SCM_I_CURRENT_THREAD;
  SCM cont;
  scm_t_contregs *continuation;
  long stack_size;
  SCM_STACKITEM * src;

  SCM_FLUSH_REGISTER_WINDOWS;
  stack_size = scm_stack_size (thread->continuation_base);
  continuation = scm_gc_malloc (sizeof (scm_t_contregs)
				+ (stack_size - 1) * sizeof (SCM_STACKITEM),
				"continuation");
  continuation->num_stack_items = stack_size;
  continuation->dynenv = scm_i_dynwinds ();
  continuation->throw_value = SCM_EOL;
  continuation->root = thread->continuation_root;
  continuation->dframe = scm_i_last_debug_frame ();
  src = thread->continuation_base;
  SCM_NEWSMOB (cont, scm_tc16_continuation, continuation);

#if ! SCM_STACK_GROWS_UP
  src -= stack_size;
#endif
  continuation->offset = continuation->stack - src;
  memcpy (continuation->stack, src, sizeof (SCM_STACKITEM) * stack_size);

  *first = !SCM_I_SETJMP (continuation->jmpbuf);
  if (*first)
    {
#ifdef __ia64__
      continuation->backing_store_size =
	(char *) scm_ia64_ar_bsp(&continuation->jmpbuf.ctx)
	-
	(char *) thread->register_backing_store_base;
      continuation->backing_store = NULL;
      continuation->backing_store =
        scm_gc_malloc (continuation->backing_store_size,
		       "continuation backing store");
      memcpy (continuation->backing_store,
              (void *) thread->register_backing_store_base,
              continuation->backing_store_size);
#endif
      return cont;
    }
  else
    {
      SCM ret = continuation->throw_value;
      continuation->throw_value = SCM_BOOL_F;
      return ret;
    }
}
