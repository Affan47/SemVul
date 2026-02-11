output_inline_function (tree fndecl)
{
  enum debug_info_type old_write_symbols = write_symbols;
  const struct gcc_debug_hooks *const old_debug_hooks = debug_hooks;
  struct function *f = DECL_SAVED_INSNS (fndecl);

  old_cfun = cfun;
  cfun = f;
  current_function_decl = fndecl;

  set_new_last_label_num (f->inl_max_label_num);


  DECL_DEFER_OUTPUT (fndecl) = 0;


  if (f->no_debugging_symbols)
    {
      write_symbols = NO_DEBUG;
      debug_hooks = &do_nothing_debug_hooks;
    }


  input_location = DECL_SOURCE_LOCATION (fndecl);


  rest_of_compilation (fndecl);
  DECL_INLINE (fndecl) = 0;

  cfun = old_cfun;
  current_function_decl = old_cfun ? old_cfun->decl : 0;
  write_symbols = old_write_symbols;
  debug_hooks = old_debug_hooks;
}
