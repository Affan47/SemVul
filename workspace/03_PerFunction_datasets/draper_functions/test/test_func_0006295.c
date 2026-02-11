backtrace_initialize (struct backtrace_state *state, int descriptor,
		      backtrace_error_callback error_callback,
		      void *data, fileline *fileline_fn)
{
  int found_sym;
  int found_dwarf;
  syminfo elf_syminfo_fn;
  fileline elf_fileline_fn;
  struct phdr_data pd;

  if (!elf_add (state, descriptor, 0, error_callback, data, &elf_fileline_fn,
		&found_sym, &found_dwarf))
    return 0;

  pd.state = state;
  pd.error_callback = error_callback;
  pd.data = data;
  pd.fileline_fn = fileline_fn;
  pd.found_sym = &found_sym;
  pd.found_dwarf = &found_dwarf;

  dl_iterate_phdr (phdr_callback, (void *) &pd);

  elf_syminfo_fn = found_sym ? elf_syminfo : elf_nosyms;
  if (!state->threaded)
    {
      if (state->syminfo_fn == NULL || found_sym)
	state->syminfo_fn = elf_syminfo_fn;
    }
  else
    {
      __sync_bool_compare_and_swap (&state->syminfo_fn, NULL, elf_syminfo_fn);
      if (found_sym)
	__sync_bool_compare_and_swap (&state->syminfo_fn, elf_nosyms,
				      elf_syminfo_fn);
    }

  if (!state->threaded)
    {
      if (state->fileline_fn == NULL || state->fileline_fn == elf_nodebug)
	*fileline_fn = elf_fileline_fn;
    }
  else
    {
      fileline current_fn;


      current_fn = state->fileline_fn;
      while (!__sync_bool_compare_and_swap (&state->fileline_fn, current_fn,
					    current_fn))
	current_fn = state->fileline_fn;
      if (current_fn == NULL || current_fn == elf_nodebug)
	*fileline_fn = elf_fileline_fn;
    }

  return 1;
}
