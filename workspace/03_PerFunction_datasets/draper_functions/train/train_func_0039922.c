cgraph_finalize_compilation_unit (void)
{
  timevar_push (TV_CGRAPH);


  finalize_size_functions ();


  finish_aliases_1 ();

  if (!quiet_flag)
    {
      fprintf (stderr, "\nAnalyzing compilation unit\n");
      fflush (stderr);
    }


  cgraph_analyze_functions ();


  finish_aliases_1 ();


  cgraph_analyze_functions ();


  cgraph_optimize ();

  timevar_pop (TV_CGRAPH);
}
