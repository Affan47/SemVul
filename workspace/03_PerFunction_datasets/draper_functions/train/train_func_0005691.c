pass_init_dump_file (struct opt_pass *pass)
{

  if (pass->static_pass_number != -1)
    {
      timevar_push (TV_DUMP);
      bool initializing_dump = !dump_initialized_p (pass->static_pass_number);
      dump_file_name = get_dump_file_name (pass->static_pass_number);
      dump_start (pass->static_pass_number, &dump_flags);
      if (dump_file && current_function_decl)
        dump_function_header (dump_file, current_function_decl, dump_flags);
      if (initializing_dump
	  && dump_file && (dump_flags & TDF_GRAPH)
	  && cfun && (cfun->curr_properties & PROP_cfg))
	clean_graph_dump_file (dump_file_name);
      timevar_pop (TV_DUMP);
      return initializing_dump;
    }
  else
    return false;
}
