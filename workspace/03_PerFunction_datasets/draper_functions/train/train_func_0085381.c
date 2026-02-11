C_callback_adjust_stack(C_word *a, int size)
{
  if(!chicken_is_running && !C_in_stackp((C_word)a)) {
    if(debug_mode)
      C_dbg(C_text("debug"),
	    C_text("callback invoked in lower stack region - adjusting limits:\n"
		   "[debug]   current:  \t%p\n"
		   "[debug]   previous: \t%p (bottom) - %p (limit)\n"),
	    a, stack_bottom, C_stack_limit);

#if C_STACK_GROWS_DOWNWARD
    C_stack_limit = (C_word *)((C_byte *)a - stack_size);
    stack_bottom = a + size;
#else
    C_stack_limit = (C_word *)((C_byte *)a + stack_size);
    stack_bottom = a;
#endif

    if(debug_mode)
      C_dbg(C_text("debug"), C_text("new:      \t%p (bottom) - %p (limit)\n"),
	    stack_bottom, C_stack_limit);
  }
}
