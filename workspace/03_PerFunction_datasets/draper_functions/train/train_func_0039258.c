dump_gimple_omp_sections (pretty_printer *buffer, gimple gs, int spc,
			  int flags)
{
  if (flags & TDF_RAW)
    {
      dump_gimple_fmt (buffer, spc, flags, "%G <%+BODY <%S>%nCLAUSES <", gs,
		       gimple_omp_body (gs));
      dump_omp_clauses (buffer, gimple_omp_sections_clauses (gs), spc, flags);
      dump_gimple_fmt (buffer, spc, flags, " >");
    }
  else
    {
      pp_string (buffer, "#pragma omp sections");
      if (gimple_omp_sections_control (gs))
	{
	  pp_string (buffer, " <");
	  dump_generic_node (buffer, gimple_omp_sections_control (gs), spc,
			     flags, false);
	  pp_character (buffer, '>');
	}
      dump_omp_clauses (buffer, gimple_omp_sections_clauses (gs), spc, flags);
      if (!gimple_seq_empty_p (gimple_omp_body (gs)))
	{
	  newline_and_indent (buffer, spc + 2);
	  pp_character (buffer, '{');
	  pp_newline (buffer);
	  dump_gimple_seq (buffer, gimple_omp_body (gs), spc + 4, flags);
	  newline_and_indent (buffer, spc + 2);
	  pp_character (buffer, '}');
	}
    }
}
