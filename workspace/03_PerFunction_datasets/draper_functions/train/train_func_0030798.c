cpp_scan_nooutput (cpp_reader *pfile)
{


  pfile->buffer->return_at_eof = true;

  if (CPP_OPTION (pfile, traditional))
    while (_cpp_read_logical_line_trad (pfile))
      ;
  else
    while (cpp_get_token (pfile)->type != CPP_EOF)
      ;
}
