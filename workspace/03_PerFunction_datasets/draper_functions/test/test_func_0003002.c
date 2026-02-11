push_command_line_include (void)
{
  while (include_cursor < deferred_count)
    {
      struct deferred_opt *opt = &deferred_opts[include_cursor++];

      if (!cpp_opts->preprocessed && opt->code == OPT_include
	  && cpp_push_include (parse_in, opt->arg))
	return;
    }

  if (include_cursor == deferred_count)
    {
      include_cursor++;

      cpp_opts->warn_unused_macros = warn_unused_macros;

      if (!cpp_opts->preprocessed)
	cpp_change_file (parse_in, LC_RENAME, this_input_filename);


      line_table->trace_includes = cpp_opts->print_include_names;
    }
}
