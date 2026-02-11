c_common_parse_file (void)
{
  unsigned int i;

  i = 0;
  for (;;)
    {
      c_finish_options ();
      pch_init ();
      push_file_scope ();
      c_parse_file ();
      pop_file_scope ();

      if (debug_hooks->start_end_main_source_file)
	(*debug_hooks->end_source_file) (0);
      if (++i >= num_in_fnames)
	break;
      cpp_undef_all (parse_in);
      cpp_clear_file_cache (parse_in);
      this_input_filename
	= cpp_read_main_file (parse_in, in_fnames[i]);


      if (!this_input_filename)
	break;
    }
}
