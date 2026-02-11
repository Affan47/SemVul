do_diagnostic (pfile, code, print_dir)
     cpp_reader *pfile;
     int code;
     int print_dir;
{
  if (_cpp_begin_message (pfile, code,
			  pfile->cur_token[-1].line,
			  pfile->cur_token[-1].col))
    {
      if (print_dir)
	fprintf (stderr, "#%s ", pfile->directive->name);
      pfile->state.prevent_expansion++;
      cpp_output_line (pfile, stderr);
      pfile->state.prevent_expansion--;
    }
}
