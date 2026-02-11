cgraph_finalize_compilation_unit (void)
{
  timevar_push (TV_CGRAPH);


  if (flag_lto)
    lto_streamer_hooks_init ();


  current_function_decl = NULL;
  set_cfun (NULL);


  finalize_size_functions ();


  finish_aliases_1 ();
  handle_alias_pairs ();

  if (!quiet_flag)
    {
      fprintf (stderr, "\nAnalyzing compilation unit\n");
      fflush (stderr);
    }

  if (flag_dump_passes)
    dump_passes ();


  cgraph_analyze_functions ();


  finish_aliases_1 ();
  handle_alias_pairs ();


  cgraph_analyze_functions ();


  cgraph_optimize ();

  timevar_pop (TV_CGRAPH);
}
