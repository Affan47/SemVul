do_line_change (cpp_reader *pfile, const cpp_token *token,
		source_location src_loc, int parsing_args)
{
  if (define_queue || undef_queue)
    dump_queued_macros (pfile);

  if (token->type == CPP_EOF || parsing_args)
    return;

  maybe_print_line (src_loc);
  print.prev = 0;
  print.source = 0;


  if (!CPP_OPTION (pfile, traditional))
    {
      int spaces = LOCATION_COLUMN (src_loc) - 2;
      print.printed = 1;

      while (-- spaces >= 0)
	putc (' ', print.outf);
    }
}
